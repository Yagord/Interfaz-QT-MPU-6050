#include "ventanaPrincipal.h"

#include "ui_ventana.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QList>
#include <QDebug>
#include <QScrollBar>


Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    inicializar();
    conexiones();
}



Ventana::~Ventana()
{
    delete ui;
}


void Ventana::inicializar()
{
    serial=new QSerialPort(this);
    //timer.start();
    file.setFileName("out.txt");
    ui->setupUi(this);
    graficos=new Graficos;
    ui->tiempo->setValidator(new QIntValidator(0,200,this));
    for(int i = 0; i < QSerialPortInfo::availablePorts().size(); i++)
    {
        QSerialPortInfo info=QSerialPortInfo::availablePorts().at(i);
        ui->portNameCB->addItem(info.portName());
    }
    ui->baudRateCB->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateCB->addItem(QStringLiteral("57600"), QSerialPort::Baud57600);
    ui->baudRateCB->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateCB->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateCB->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
}

void Ventana::conexiones()
{

    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(openSerialPort()));
    connect(ui->actionConectar,SIGNAL(triggered()),this,SLOT(openSerialPort()));
    connect(ui->stopButton,SIGNAL(clicked()),this,SLOT(closeSerialPort()));
    connect(ui->actionParar,SIGNAL(triggered()),this,SLOT(closeSerialPort()));
    connect(ui->baudRateCB,SIGNAL(currentTextChanged(QString)),this,SLOT(cambiarBaudRateCB()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(closeWindow()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(closeWindow()));
    connect(this,SIGNAL(emitlinea(QStringList)),this,SLOT(imprimir(QStringList)));
    //connect(this, SIGNAL(enviardatosgrafico(QStringList,QList<double>)), graficos, SLOT(Graficar(QStringList,QList<double>)));
    //connect(this, SIGNAL(enviardatosgrafico(QStringList,QList<double>)), graficos, SLOT(show()));
    connect(this,SIGNAL(emitdato(QStringList,double)),graficos,SLOT(show()));
    connect(this,SIGNAL(emitdato(QStringList,double)),graficos,SLOT(realtimeDataSlot(QStringList,double)));

}

void Ventana::readData(){
    if (timer.elapsed()/1000.0<=Tiempo.toDouble()){
        while (serial->canReadLine()){
            QByteArray serialData = serial->readLine();
            dato=QString(serialData);
            QStringList linea=dato.split(" ");
            if(linea.size()==6){
                datos.append(dato);

                if(datos.size()==1){//Cuando se agrega el primer dato, se inicia el tiempo.
                    timer.start();                    
                }
                listaTiempos.append(timer.elapsed()/1000.0);
                emit emitlinea(linea);
                if(datos.size()%5==0)//Cada 5 datos se grafica
                    emit emitdato(linea,timer.elapsed()/1000.0);
                emit enviardatosgrafico(datos,listaTiempos);
            }
        }
    }else{
        serial->close();
    }
}


void Ventana::openSerialPort()
{
    file.reset();
    datos.clear();          //Limpieza de las listas
    listaTiempos.clear();
    if (ui->tiempo->text()==""){
        QMessageBox::information(this,"Ingrese tiempo","Debe ingresar Tiempo");

    }
    else{
        Tiempo=ui->tiempo->text();
        serial->setPortName(ui->portNameCB->currentText());
        serial->setBaudRate(ui->baudRateCB->currentText().toInt());
        QTextStream(stdout)<<"Baudios: "<< serial->baudRate();
        QTextStream(stdout)<<"portName"<< serial->portName();
        serial->setStopBits(QSerialPort::OneStop);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if (serial->open(QIODevice::ReadWrite)){
            //serial->dataTerminalReadyChanged(true);
            //serial->requestToSendChanged(true);
            timer.start();
            QMessageBox::information(this,"Puerto Abierto","El puerto se ha abierto");
        } else {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
        }
    }
}

void Ventana::closeSerialPort()
{
    datos.clear();
    listaTiempos.clear();
    if (serial->isOpen()){
        serial->close();
        //lector->timer.restart();
        QMessageBox::information(this,"Cerrar Puerto","Puerto Cerrado");
        QTextStream(stdout)<<"Cerrado";
    }
    else {
         QMessageBox::information(this,"Cerrar Puerto","El puerto ya estaba cerrado");
    }
}

void Ventana::closeWindow(){
    qApp->quit();
}


void Ventana::on_cleanButton_clicked()
{
    ui->plainTextEdit->clear();
}

void Ventana::cambiarBaudRateCB()
{
    ui->baudRate->setText("Baudios: "+ui->baudRateCB->currentText());
}

void Ventana::imprimir(QStringList linea)
{

    //QTextStream(stdout)<<"Tiempo:"<<timer.elapsed()/1000.0<<" Muestras:"<<datos.size()<<" AcX:"<<linea.at(0)<<" AcY:"<<linea.at(1)<<" AcZ:"<<linea.at(2)<<" GyX:"<<linea.at(3)<<" GyY:"<<linea.at(4)<<" GyZ:"<<linea.at(5)<<endl;
    QTextStream(stdout)<<"Tiempo:"<<timer.elapsed()/1000.0<<" Muestras:"<<datos.size()<<" AcX:"<<linea.at(0)<<" AcY:"<<linea.at(1)<<" AcZ:"<<linea.at(2)<<endl;
    ui->plainTextEdit->insertPlainText(QString::number(timer.elapsed()/1000.0)+" "+dato);
    QScrollBar *bar = ui->plainTextEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << QString::number(timer.elapsed()/1000.0)+" "+linea.at(0)+" "+linea.at(1)+" "+linea.at(2)+" "+linea.at(3)+" "+linea.at(4)+" "+linea.at(5);
    }
    file.close();
}


void Ventana::on_portNameCB_currentTextChanged()
{
    QList<QSerialPortInfo> puertos=QSerialPortInfo::availablePorts();
    for (int i = 0; i < puertos.size(); i++) {
        QSerialPortInfo info=puertos.at(i);
        if (info.portName()==ui->portNameCB->currentText()){
            ui->portNamelabel->setText("Puerto: "+info.portName());
            ui->description->setText("Descripcion: "+info.description());
            ui->serialNumber->setText("Numero de Serie: "+info.serialNumber());
            break;
        }
    }
}
