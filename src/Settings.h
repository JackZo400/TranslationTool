#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QVariant>

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject* parent = nullptr);

    void setValue(const QString& key, const QVariant& value);
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;

    // 便捷方法
    QString getApiKey() const;
    void setApiKey(const QString& apiKey);
    QString getSourceLanguage() const;
    void setSourceLanguage(const QString& language);
    QString getTargetLanguage() const;
    void setTargetLanguage(const QString& language);
    int getDomain() const;
    void setDomain(int domain);

private:
    QSettings m_settings;
};

#endif