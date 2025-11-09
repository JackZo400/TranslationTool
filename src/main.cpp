#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QStyleFactory>
#include <QFontDatabase>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("专业文档翻译工具");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("YourCompany");

    // 设置Windows风格
    app.setStyle(QStyleFactory::create("Fusion"));

    // 设置字体 - 确保中文字体显示正常
    QFont font("Microsoft YaHei", 10);
    app.setFont(font);

    // 加载翻译文件（可选）
    QTranslator translator;
    if (translator.load(QLocale::system(), "translation", "_", ":/i18n")) {
        app.installTranslator(&translator);
    }

    MainWindow window;
    window.show();

    return app.exec();
}