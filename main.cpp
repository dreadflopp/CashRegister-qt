#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QFontDatabase::addApplicationFont(":fonts/OpenSans-Regular.tff");
    QFile file(":/qss/default.qss");
    file.open(QFile::ReadOnly);
    QString stylesheet = file.readAll();
    a.setStyleSheet(stylesheet);
    */
    MainWindow w;
    w.runTests();
    w.show();
    return a.exec();
}
