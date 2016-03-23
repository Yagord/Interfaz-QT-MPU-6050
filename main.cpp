#include "mainwindow.h"
#include "login.h"
#include "graficos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.setWindowTitle("Lectura Serial");
    MainWindow w;
    w.show();

    return a.exec();
}
