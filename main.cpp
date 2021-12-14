#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QCoreApplication::​setAttribute(Qt::AA_DontUseNativeMenuBar); # меню не показывалось
    MainWindow w;
    w.show();
    return a.exec();
}
