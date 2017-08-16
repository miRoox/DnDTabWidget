#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCommandLineParser parser;
    parser.addOptions({
        {"x","move window to indicated left side position on screen","posX","100"},
        {"y","move window to indicated top position on screen","posY","100"}
        /*name, description, value name, default value*/
    });
    parser.addPositionalArgument("filePath","file to open");
    parser.process(a);

    bool converted;
    auto x = parser.value("x").toInt(&converted);
    if(!converted)
        x = 100;
    auto y = parser.value("y").toInt(&converted);
    if(!converted)
        y = 100;

    QStringList filePaths = parser.positionalArguments();

    MainWindow w;
    w.move(x,y);
    w.show();
    for(const QString& filePath : filePaths) {
        w.openFile(filePath);
    }

    return a.exec();
}
