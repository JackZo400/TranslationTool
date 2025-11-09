#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextDocument>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , translationEngine(new TranslationEngine(this))
    , fileHandler(new FileHandler(this))
{
    setupUI();
    setupConnections();
    loadSettings();

    setWindowTitle("专业文档翻译工具 v1.0");
    setMinimumSize(1200, 800);

    // 设置初始状态
    updateCharacterCount();
}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // 控制面板
    QHBoxLayout* controlLayout = new QHBoxLayout();

    openFileBtn = new QPushButton("打开文件", this);
    saveFileBtn = new QPushButton("保存翻译", this);
    translateBtn = new QPushButton("开始翻译", this);

    sourceLangCombo = new QComboBox(this);
    targetLangCombo = new QComboBox(this);
    fileFormatCombo = new QComboBox(this);
    domainCombo = new QComboBox(this);

    // 初始化语言选项
    QStringList languages = {
        "自动检测", "英语", "中文", "日语", "韩语",
        "法语", "德语", "西班牙语", "俄语"
    };

    sourceLangCombo->addItems(languages);
    targetLangCombo->addItems(languages);
    sourceLangCombo->setCurrentText("英语");
    targetLangCombo->setCurrentText("中文");

    // 文件格式选项
    QStringList formats = { "自动检测", "TXT", "DOCX", "PDF", "HTML" };
    fileFormatCombo->addItems(formats);

    // 专业领域选项
    QStringList domains = { "通用", "医学", "法律", "技术", "学术", "商务" };
    domainCombo->addItems(domains);

    // API密钥输入
    QLineEdit* apiKeyEdit = new QLineEdit(this);
    apiKeyEdit->setPlaceholderText("输入翻译API密钥");
    apiKeyEdit->setEchoMode(QLineEdit::Password);

    controlLayout->addWidget(new QLabel("源语言:"));
    controlLayout->addWidget(sourceLangCombo);
    controlLayout->addWidget(new QLabel("目标语言:"));
    controlLayout->addWidget(targetLangCombo);
    controlLayout->addWidget(new QLabel("领域:"));
    controlLayout->addWidget(domainCombo);
    controlLayout->addWidget(new QLabel("格式:"));
    controlLayout->addWidget(fileFormatCombo);
    controlLayout->addWidget(apiKeyEdit);
    controlLayout->addWidget(openFileBtn);
    controlLayout->addWidget(translateBtn);
    controlLayout->addWidget(saveFileBtn);
    controlLayout->addStretch();

    // 文本编辑区域
    QHBoxLayout* textLayout = new QHBoxLayout();

    QGroupBox* sourceGroup = new QGroupBox("原文", this);
    QGroupBox* targetGroup = new QGroupBox("译文", this);

    sourceTextEdit = new QTextEdit(this);
    translatedTextEdit = new QTextEdit(this);

    sourceTextEdit->setPlaceholderText("在此输入文本或打开文件...");
    translatedTextEdit->setPlaceholderText("翻译结果将显示在这里...");

    // 字符计数标签
    charCountLabel = new QLabel("字符数: 0", this);

    QVBoxLayout* sourceLayout = new QVBoxLayout(sourceGroup);
    sourceLayout->addWidget(sourceTextEdit);
    sourceLayout->addWidget(charCountLabel);

    QVBoxLayout* targetLayout = new QVBoxLayout(targetGroup);
    targetLayout->addWidget(translatedTextEdit);

    textLayout->addWidget(sourceGroup);
    textLayout->addWidget(targetGroup);

    // 进度条
    progressBar = new QProgressBar(this);
    progressBar->setVisible(false);

    // 状态标签
    statusLabel = new QLabel("就绪", this);

    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(textLayout);
    mainLayout->addWidget(progressBar);
    mainLayout->addWidget(statusLabel);

    // 连接API密钥输入
    connect(apiKeyEdit, &QLineEdit::textChanged, this, &MainWindow::onApiKeyChanged);
    connect(domainCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &MainWindow::onDomainChanged);
    connect(sourceTextEdit, &QTextEdit::textChanged, this, &MainWindow::updateCharacterCount);
}

void MainWindow::setupConnections()
{
    connect(openFileBtn, &QPushButton::clicked, this, &MainWindow::openSourceFile);
    connect(saveFileBtn, &QPushButton::clicked, this, &MainWindow::saveTranslatedFile);
    connect(translateBtn, &QPushButton::clicked, this, &MainWindow::startTranslation);

    connect(translationEngine, &TranslationEngine::translationProgress,
        this, &MainWindow::translationProgress);
    connect(translationEngine, &TranslationEngine::translationFinished,
        this, &MainWindow::translationFinished);
    connect(translationEngine, &TranslationEngine::errorOccurred,
        this, &MainWindow::translationError);
}

void MainWindow::openSourceFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "选择要翻译的文件",
        QDir::homePath(),
        "所有支持的文件 (*.txt *.docx *.pdf *.html *.xml *.json);;"
        "文本文件 (*.txt);;Word文档 (*.docx);;PDF文件 (*.pdf);;网页文件 (*.html *.xml);;JSON文件 (*.json);;所有文件 (*.*)"
    );

    if (!filePath.isEmpty()) {
        currentSourceFile = filePath;
        QString content;

        if (fileHandler->readFile(filePath, content)) {
            sourceTextEdit->setPlainText(content);
            statusLabel->setText(QString("已加载文件: %1").arg(QFileInfo(filePath).fileName()));
        }
        else {
            QMessageBox::warning(this, "错误", "无法读取文件: " + filePath);
        }
    }
}

void MainWindow::saveTranslatedFile()
{
    QString translatedText = translatedTextEdit->toPlainText();
    if (translatedText.isEmpty()) {
        QMessageBox::information(this, "提示", "没有可保存的翻译内容");
        return;
    }

    QString defaultName = "translated_" + QFileInfo(currentSourceFile).baseName() + ".txt";
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "保存翻译文件",
        QDir::homePath() + "/" + defaultName,
        "文本文件 (*.txt);;Word文档 (*.docx);;PDF文件 (*.pdf);;网页文件 (*.html)"
    );

    if (!filePath.isEmpty()) {
        if (fileHandler->writeFile(filePath, translatedText)) {
            statusLabel->setText(QString("已保存到: %1").arg(QFileInfo(filePath).fileName()));
        }
        else {
            QMessageBox::warning(this, "错误", "保存文件失败: " + filePath);
        }
    }
}

void MainWindow::startTranslation()
{
    QString sourceText = sourceTextEdit->toPlainText().trimmed();
    if (sourceText.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入要翻译的文本或打开文件");
        return;
    }

    if (sourceText.length() > 100000) {
        QMessageBox::warning(this, "警告", "文本过长，建议分割处理");
        return;
    }

    progressBar->setVisible(true);
    progressBar->setValue(0);
    translateBtn->setEnabled(false);
    translatedTextEdit->clear();

    statusLabel->setText("正在翻译...");
    translationEngine->translateText(sourceText);
}

void MainWindow::translationProgress(int value)
{
    progressBar->setValue(value);
    statusLabel->setText(QString("正在翻译... %1%").arg(value));
}

void MainWindow::translationFinished(const QString& translatedText)
{
    translatedTextEdit->setPlainText(translatedText);
    progressBar->setVisible(false);
    translateBtn->setEnabled(true);
    statusLabel->setText("翻译完成");
}

void MainWindow::translationError(const QString& error)
{
    QMessageBox::critical(this, "翻译错误", "翻译过程中发生错误:\n" + error);
    progressBar->setVisible(false);
    translateBtn->setEnabled(true);
    statusLabel->setText("翻译失败: " + error);
}

void MainWindow::loadSettings()
{
    QSettings settings("YourCompany", "TranslationTool");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    sourceLangCombo->setCurrentText(settings.value("sourceLang", "英语").toString());
    targetLangCombo->setCurrentText(settings.value("targetLang", "中文").toString());
    domainCombo->setCurrentIndex(settings.value("domain", 0).toInt());
}

void MainWindow::saveSettings()
{
    QSettings settings("YourCompany", "TranslationTool");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("sourceLang", sourceLangCombo->currentText());
    settings.setValue("targetLang", targetLangCombo->currentText());
    settings.setValue("domain", domainCombo->currentIndex());
}

void MainWindow::onApiKeyChanged(const QString& key)
{
    if (translationEngine) {
        translationEngine->setApiKey(key);
    }
}

void MainWindow::onDomainChanged(int index)
{
    if (translationEngine) {
        Domain domain = static_cast<Domain>(index);
        translationEngine->setDomain(domain);
    }
}

void MainWindow::updateCharacterCount()
{
    if (sourceTextEdit) {
        int count = sourceTextEdit->toPlainText().length();
        if (charCountLabel) {
            charCountLabel->setText(QString("字符数: %1").arg(count));
        }
    }
}

MainWindow::~MainWindow()
{
    saveSettings();
}