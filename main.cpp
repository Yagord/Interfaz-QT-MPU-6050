#include "ventana.h"
#include "login.h"
#include "graficos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Ventana w;
    //w.setWindowTitle("Lectura Serial");
    Ventana w;
    w.show();

    return a.exec();
}
