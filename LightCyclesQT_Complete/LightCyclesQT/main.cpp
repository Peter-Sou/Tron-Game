#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Tron: Light Cycles QT");
    w.setWindowIcon(QIcon(":resources/images/icon.ico"));
    w.show();
    return a.exec();
}
