#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

// 支持的文件格式
enum class FileFormat {
    TXT,
    DOCX,
    PDF,
    HTML,
    XML,
    JSON
};

class FileHandler : public QObject
{
    Q_OBJECT

public:
    explicit FileHandler(QObject* parent = nullptr);

    bool readFile(const QString& filePath, QString& content);
    bool writeFile(const QString& filePath, const QString& content);
    FileFormat detectFormat(const QString& filePath);
    QString getFormatExtension(FileFormat format);

    // 高级功能：保持格式的文档处理
    bool extractTextFromDocx(const QString& filePath, QString& content);
    bool extractTextFromPdf(const QString& filePath, QString& content);
    bool preserveFormatting(const QString& sourcePath, const QString& targetPath,
        const QString& translatedContent);

private:
    QString cleanText(const QString& text);
    bool isBinaryFormat(FileFormat format);
};

#endif