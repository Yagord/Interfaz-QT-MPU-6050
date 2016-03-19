#ifndef VENTANA_H
#define VENTANA_H

#include "graficos.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QElapsedTimer>
#include <lectorserial.h>

namespace Ui {
class Ventana;
}

class Ventana : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();

signals:
    void emitlinea(QStringList);
    void emitdato(QStringList,double);
    void enviardatosgrafico(QStringList,QList<double>);
    void vamosagraficar(QList<boolean> Checkboxs);

    //void mostrargrafico();

private slots:
    void on_portNameCB_currentTextChanged();
    void readData();
    void openSerialPort();
    void closeSerialPort();
    void closeWindow();
    void on_cleanButton_clicked();
    void cambiarBaudRateCB();
    void print(QStringList linea);    

private:
    Ui::Ventana *ui;
    QSerialPort *serial;
    LectorSerial *lector;
    QStringList datos;
    int samplesNumber;
    QList<double> listaTiempos;
    QString serialReaded;
    QElapsedTimer timer;
    Graficos *graficos;
    void inicializar();
    void conexiones();
    //QSerialPort *serial;
    //QString serialBuffer;
    QFile file;
    QList<boolean> GetGraphicsCheckboxs();


};

#endif // VENTANA_H
