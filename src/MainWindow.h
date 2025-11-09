#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QSettings>
#include <QLabel>
#include "TranslationEngine.h"
#include "FileHandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openSourceFile();
    void saveTranslatedFile();
    void startTranslation();
    void translationProgress(int value);
    void translationFinished(const QString& translatedText);
    void translationError(const QString& error);
    void onApiKeyChanged(const QString& key);
    void onDomainChanged(int index);
    void updateCharacterCount();

private:
    void setupUI();
    void setupConnections();
    void loadSettings();
    void saveSettings();

    // UI Components
    QTextEdit* sourceTextEdit;
    QTextEdit* translatedTextEdit;
    QComboBox* sourceLangCombo;
    QComboBox* targetLangCombo;
    QComboBox* fileFormatCombo;
    QComboBox* domainCombo;
    QPushButton* openFileBtn;
    QPushButton* saveFileBtn;
    QPushButton* translateBtn;
    QProgressBar* progressBar;
    QLabel* charCountLabel;
    QLabel* statusLabel;

    // Core components
    TranslationEngine* translationEngine;
    FileHandler* fileHandler;

    QString currentSourceFile;
    QString currentTargetFile;
};

#endif