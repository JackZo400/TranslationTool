#ifndef TRANSLATIONENGINE_H
#define TRANSLATIONENGINE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QRegularExpression>

// 支持的专业领域
enum class Domain {
    General,
    Medical,
    Legal,
    Technical,
    Academic,
    Business
};

class TranslationEngine : public QObject
{
    Q_OBJECT

public:
    explicit TranslationEngine(QObject* parent = nullptr);
    ~TranslationEngine();

    void setApiKey(const QString& key);
    void setDomain(Domain domain);
    void setSourceLanguage(const QString& lang);
    void setTargetLanguage(const QString& lang);

public slots:
    void translateText(const QString& text);
    void translateBatch(const QStringList& texts);

signals:
    void translationProgress(int progress);
    void translationFinished(const QString& translatedText);
    void batchTranslationFinished(const QStringList& translatedTexts);
    void errorOccurred(const QString& error);

private slots:
    void performMockTranslation(const QString& text);

private:
    QString performMockTranslationSync(const QString& text);
    void performSingleTranslation(const QString& text);
    QString buildRequestData(const QString& text);
    QString parseTranslationResponse(const QByteArray& response);
    QStringList splitText(const QString& text, int maxLength = 4000);
    QString postProcessTranslation(const QString& text);
    QString applyTerminology(const QString& text);
    void loadTerminology();

    QString apiKey;
    QString sourceLang;
    QString targetLang;
    Domain currentDomain;
    QMutex translationMutex;

    // 专业术语词典
    QMap<QString, QString> medicalTerms;
    QMap<QString, QString> legalTerms;
    QMap<QString, QString> technicalTerms;
};

#endif