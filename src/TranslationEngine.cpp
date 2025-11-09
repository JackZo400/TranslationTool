#include "TranslationEngine.h"

TranslationEngine::TranslationEngine(QObject* parent)
    : QObject(parent)
    , sourceLang("en")
    , targetLang("zh")
    , currentDomain(Domain::General)
{
    loadTerminology();
}

TranslationEngine::~TranslationEngine()
{
    // 清理资源
}

void TranslationEngine::setApiKey(const QString& key)
{
    QMutexLocker locker(&translationMutex);
    apiKey = key;
}

void TranslationEngine::setDomain(Domain domain)
{
    QMutexLocker locker(&translationMutex);
    currentDomain = domain;
}

void TranslationEngine::setSourceLanguage(const QString& lang)
{
    QMutexLocker locker(&translationMutex);
    sourceLang = lang;
}

void TranslationEngine::setTargetLanguage(const QString& lang)
{
    QMutexLocker locker(&translationMutex);
    targetLang = lang;
}

void TranslationEngine::translateText(const QString& text)
{
    if (text.isEmpty()) {
        emit translationFinished("");
        return;
    }

    // 分割长文本
    QStringList textChunks = splitText(text);
    if (textChunks.isEmpty()) {
        emit errorOccurred("文本分割失败");
        return;
    }

    if (textChunks.size() == 1) {
        // 单次翻译
        performSingleTranslation(textChunks.first());
    }
    else {
        // 批量翻译
        translateBatch(textChunks);
    }
}

void TranslationEngine::translateBatch(const QStringList& texts)
{
    QStringList translatedTexts;
    int completed = 0;

    for (const QString& text : texts) {
        // 使用模拟翻译
        QString translated = performMockTranslationSync(text);
        translatedTexts << translated;
        completed++;

        int progress = (completed * 100) / texts.size();
        emit translationProgress(progress);

        // 短暂延迟以模拟网络请求
        QThread::msleep(100);
    }

    emit batchTranslationFinished(translatedTexts);
}

void TranslationEngine::performSingleTranslation(const QString& text)
{
    // 使用模拟翻译
    performMockTranslation(text);
}

void TranslationEngine::performMockTranslation(const QString& text)
{
    // 模拟异步翻译过程
    QTimer::singleShot(1000, [this, text]() {
        QString translatedText = performMockTranslationSync(text);
        emit translationFinished(translatedText);
        });
}

QString TranslationEngine::performMockTranslationSync(const QString& text)
{
    // 模拟翻译结果
    QString translatedText = text;

    // 简单的模拟翻译规则
    if (sourceLang == "en" && targetLang == "zh") {
        // 这里可以添加一些简单的英译中规则
        translatedText = "【翻译结果】" + text;
    }
    else if (sourceLang == "zh" && targetLang == "en") {
        translatedText = "【Translation】" + text;
    }
    else {
        translatedText = "【Translated】" + text;
    }

    // 应用术语替换
    translatedText = applyTerminology(translatedText);

    // 后处理
    translatedText = postProcessTranslation(translatedText);

    return translatedText;
}

QString TranslationEngine::parseTranslationResponse(const QByteArray& response)
{
    // 模拟解析响应
    return "Parsed: " + QString(response);
}

QStringList TranslationEngine::splitText(const QString& text, int maxLength)
{
    QStringList chunks;
    int start = 0;

    while (start < text.length()) {
        int end = start + maxLength;
        if (end >= text.length()) {
            chunks << text.mid(start);
            break;
        }

        // 尽量在句子边界分割
        int splitPos = text.lastIndexOf('.', end);
        if (splitPos == -1 || splitPos < start) {
            splitPos = text.lastIndexOf(' ', end);
        }
        if (splitPos == -1 || splitPos < start) {
            splitPos = end;
        }

        chunks << text.mid(start, splitPos - start + 1);
        start = splitPos + 1;
    }

    return chunks;
}

void TranslationEngine::loadTerminology()
{
    // 加载专业术语词典
    medicalTerms = {
        {"myocardial infarction", "心肌梗死"},
        {"hypertension", "高血压"},
        {"antibiotics", "抗生素"},
        {"diagnosis", "诊断"},
        {"treatment", "治疗"}
    };

    legalTerms = {
        {"plaintiff", "原告"},
        {"defendant", "被告"},
        {"jurisdiction", "司法管辖权"},
        {"contract", "合同"},
        {"lawsuit", "诉讼"}
    };

    technicalTerms = {
        {"algorithm", "算法"},
        {"blockchain", "区块链"},
        {"machine learning", "机器学习"},
        {"artificial intelligence", "人工智能"},
        {"cloud computing", "云计算"}
    };
}

QString TranslationEngine::applyTerminology(const QString& text)
{
    QString result = text;
    QMap<QString, QString>* currentTerms = nullptr;

    switch (currentDomain) {
    case Domain::Medical:
        currentTerms = &medicalTerms;
        break;
    case Domain::Legal:
        currentTerms = &legalTerms;
        break;
    case Domain::Technical:
        currentTerms = &technicalTerms;
        break;
    default:
        return result;
    }

    if (currentTerms) {
        for (auto it = currentTerms->begin(); it != currentTerms->end(); ++it) {
            // 使用正则表达式进行不区分大小写的替换
            QRegularExpression regex("\\b" + QRegularExpression::escape(it.key()) + "\\b",
                QRegularExpression::CaseInsensitiveOption);
            result.replace(regex, it.value());
        }
    }

    return result;
}

QString TranslationEngine::postProcessTranslation(const QString& text)
{
    // 后处理：修复标点、空格等
    QString result = text;

    // 修复中文标点后的空格
    result.replace(QRegularExpression("([。，；：？！])\\s+"), "\\1");

    // 确保英文单词间有空格
    result.replace(QRegularExpression("([a-zA-Z])([\\u4e00-\\u9fff])"), "\\1 \\2");
    result.replace(QRegularExpression("([\\u4e00-\\u9fff])([a-zA-Z])"), "\\1 \\2");

    // 移除多余的空格
    result.replace(QRegularExpression("\\s+"), " ");

    return result.trimmed();
}

QString TranslationEngine::buildRequestData(const QString& text)
{
    // 构建请求数据的模拟实现
    return "Request data for: " + text;
}