#include "ventanaPrincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ventana w;
    w.setWindowTitle("Lectura Serial");
    w.show();

    return a.exec();
}
