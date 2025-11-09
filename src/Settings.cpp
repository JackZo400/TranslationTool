#include "Settings.h"

Settings::Settings(QObject* parent)
    : QObject(parent)
    , m_settings("YourCompany", "TranslationTool")
{
}

void Settings::setValue(const QString& key, const QVariant& value)
{
    m_settings.setValue(key, value);
}

QVariant Settings::value(const QString& key, const QVariant& defaultValue) const
{
    return m_settings.value(key, defaultValue);
}

QString Settings::getApiKey() const
{
    return value("api_key").toString();
}

void Settings::setApiKey(const QString& apiKey)
{
    setValue("api_key", apiKey);
}

QString Settings::getSourceLanguage() const
{
    return value("source_language", "en").toString();
}

void Settings::setSourceLanguage(const QString& language)
{
    setValue("source_language", language);
}

QString Settings::getTargetLanguage() const
{
    return value("target_language", "zh").toString();
}

void Settings::setTargetLanguage(const QString& language)
{
    setValue("target_language", language);
}

int Settings::getDomain() const
{
    return value("domain", 0).toInt();
}

void Settings::setDomain(int domain)
{
    setValue("domain", domain);
}