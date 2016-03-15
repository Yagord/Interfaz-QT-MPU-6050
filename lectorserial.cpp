#include "lectorserial.h"
#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <ventana.h>
#include <QScrollBar>


LectorSerial::LectorSerial(QObject *parent) :
    QObject (parent)
{

}

void LectorSerial::readData(QSerialPort *serial, QPlainTextEdit *plainTextEdit, QString Tiempo){

    while (serial->canReadLine()){
        QTextStream(stdout)<<"Tiempo"<<Tiempo;
        QByteArray serialData = serial->readLine();
        dato=QString(serialData);
        QStringList linea=dato.split(" ");
        if(linea.size()==6){
            datos.append(dato);
            if(datos.size()==1){
                timer.start();
            }
            QTextStream(stdout)<<"Tiempo:"<<timer.elapsed()/1000.0<<" Muestras:"<<datos.size()<<" AcX:"<<linea.at(0).toInt()<<" AcY:"<<linea.at(1)<<" AcZ:"<<linea.at(2)<<" GyX:"<<linea.at(3)<<" GyY:"<<linea.at(4)<<" GyZ:"<<linea.at(5)<<endl;
            plainTextEdit->insertPlainText(dato);
            QScrollBar *bar = plainTextEdit->verticalScrollBar();
            bar->setValue(bar->maximum());
        }
    }
}

