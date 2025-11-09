#include "FileHandler.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>

FileHandler::FileHandler(QObject* parent)
    : QObject(parent)
{
}

bool FileHandler::readFile(const QString& filePath, QString& content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << filePath << file.errorString();
        return false;
    }

    FileFormat format = detectFormat(filePath);

    switch (format) {
    case FileFormat::TXT:
    case FileFormat::HTML:
    case FileFormat::XML:
    case FileFormat::JSON:
    {
        QTextStream stream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        stream.setCodec("UTF-8");
#else
        stream.setEncoding(QStringConverter::Utf8);
#endif
        content = stream.readAll();
        break;
    }
    case FileFormat::DOCX:
        return extractTextFromDocx(filePath, content);
    case FileFormat::PDF:
        return extractTextFromPdf(filePath, content);
    default:
        content = "不支持的格式";
        return false;
    }

    file.close();

    // 清理文本
    content = cleanText(content);
    return true;
}

bool FileHandler::writeFile(const QString& filePath, const QString& content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法写入文件:" << filePath << file.errorString();
        return false;
    }

    QTextStream stream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    stream.setCodec("UTF-8");
#else
    stream.setEncoding(QStringConverter::Utf8);
#endif
    stream << content;

    file.close();
    return true;
}

FileFormat FileHandler::detectFormat(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();

    if (suffix == "txt") return FileFormat::TXT;
    if (suffix == "docx") return FileFormat::DOCX;
    if (suffix == "pdf") return FileFormat::PDF;
    if (suffix == "html" || suffix == "htm") return FileFormat::HTML;
    if (suffix == "xml") return FileFormat::XML;
    if (suffix == "json") return FileFormat::JSON;

    return FileFormat::TXT; // 默认作为文本文件处理
}

QString FileHandler::getFormatExtension(FileFormat format)
{
    switch (format) {
    case FileFormat::TXT: return "txt";
    case FileFormat::DOCX: return "docx";
    case FileFormat::PDF: return "pdf";
    case FileFormat::HTML: return "html";
    case FileFormat::XML: return "xml";
    case FileFormat::JSON: return "json";
    default: return "txt";
    }
}

bool FileHandler::extractTextFromDocx(const QString& filePath, QString& content)
{
    // 简化版DOCX处理 - 实际项目中可以使用Qt的QAxObject（Windows）或第三方库
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    // 注意：这里需要实际实现DOCX解析
    // 目前返回占位符
    content = "DOCX文件解析功能需要额外实现\n";
    content += "建议使用QAxObject与Word交互或使用docx库";

    return true;
}

bool FileHandler::extractTextFromPdf(const QString& filePath, QString& content)
{
    // 简化版PDF处理 - 实际项目中可以使用Poppler或其他PDF库
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    // 注意：这里需要实际实现PDF解析
    // 目前返回占位符
    content = "PDF文件解析功能需要额外实现\n";
    content += "建议集成Poppler库或其他PDF处理库";

    return true;
}

bool FileHandler::preserveFormatting(const QString& sourcePath, const QString& targetPath,
    const QString& translatedContent)
{
    // 占位函数 - 用于保持原始文档格式
    // 实际实现需要根据具体格式处理
    return writeFile(targetPath, translatedContent);
}

QString FileHandler::cleanText(const QString& text)
{
    QString result = text;

    // 移除多余的空格和换行
    result.replace(QRegularExpression("\\s+"), " ");
    result.replace(QRegularExpression("\\n\\s*\\n"), "\n\n");

    // 清理不可见字符（保留基本的空白字符）
    result.remove(QRegularExpression("[\\x00-\\x08\\x0B-\\x0C\\x0E-\\x1F]"));

    return result.trimmed();
}

bool FileHandler::isBinaryFormat(FileFormat format)
{
    return format == FileFormat::DOCX || format == FileFormat::PDF;
}