#include "graficos.h"
#include "ui_graficos.h"
#include "ventanaPrincipal.h"

Graficos::Graficos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Graficos)
{
    inicializar();
}

Graficos::~Graficos()
{
    delete ui;
}

void Graficos::inicializar()
{
    ui->setupUi(this);

    ui->graficoAcX->addGraph(); // blue line
    ui->graficoAcX->graph(0)->setPen(QPen(Qt::blue));
    ui->graficoAcX->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    ui->graficoAcY->addGraph(); // blue line
    ui->graficoAcY->graph(0)->setPen(QPen(Qt::blue));
    ui->graficoAcY->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    ui->graficoAcZ->addGraph(); // blue line
    ui->graficoAcZ->graph(0)->setPen(QPen(Qt::blue));
    ui->graficoAcZ->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    //ui->graficoAcX->addGraph(); // red line
    //ui->graficoAcX->graph(1)->setPen(QPen(Qt::red));
    //ui->graficoAcX->graph(0)->setChannelFillGraph(ui->graficoAcX->graph(1));

    //ui->graficoAcX->addGraph(); // blue dot
    //ui->graficoAcX->graph(2)->setPen(QPen(Qt::blue));
    //ui->graficoAcX->graph(2)->setLineStyle(QCPGraph::lsNone);
    //ui->graficoAcX->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);

}

void Graficos::Graficar(QStringList datos, QList<double> Tiempos)
{
        QVector<double> AcX(datos.size());
        QVector<double> AcY(datos.size());
        QVector<double> AcZ(datos.size());
        for (int i = 0; i < datos.size(); ++i) {
            QString dato=datos.at(i);
            QStringList linea=dato.split(" ");
            bool ok;
            AcX[i]=QString(linea.at(0)).toDouble(&ok);
            AcY[i]=QString(linea.at(1)).toDouble(&ok);
            AcZ[i]=QString(linea.at(1)).toDouble(&ok);
        }
        rellenarGraficos(ui->graficoAcX,Tiempos.toVector(),AcX,"Aceleracion X");
        rellenarGraficos(ui->graficoAcY,Tiempos.toVector(),AcY,"Aceleracion Y");
        rellenarGraficos(ui->graficoAcZ,Tiempos.toVector(),AcZ,"Aceleracion Z");

}


void Graficos::realtimeDataSlot(QStringList linea,double tiempo)
{// calculate two new data points:
      // add data to lines:
    bool ok;
    double AcX=QString(linea.at(0)).toDouble(&ok);
    double AcY=QString(linea.at(1)).toDouble(&ok);
    double AcZ=QString(linea.at(2)).toDouble(&ok);
    graficartiemporeal(ui->graficoAcX,tiempo,AcX);
    graficartiemporeal(ui->graficoAcY,tiempo,AcY);
    graficartiemporeal(ui->graficoAcZ,tiempo,AcZ);
    //QTextStream(stdout)<<" AcX:"<<linea.at(0)<<" AcY:"<<linea.at(1)<<" AcZ:"<<linea.at(2)<<" GyX:"<<linea.at(3)<<" GyY:"<<linea.at(4)<<" GyZ:"<<linea.at(5)<<endl;
}



void Graficos::graficartiemporeal(QCustomPlot *grafico, double tiempo, double dato)
{
    grafico->graph(0)->addData(tiempo, dato);

    //ui->graficoAcX->graph(1)->addData(tiempo, AcX);
    // set data of dots:
    //ui->graficoAcX->graph(2)->clearData();
    //ui->graficoAcX->graph(2)->addData(tiempo, AcX+1);
    //ui->graficoAcX->graph(3)->clearData();
    //ui->graficoAcX->graph(3)->addData(tiempo, AcX+2);
    // remove data of lines that's outside visible range:

    grafico->graph(0)->removeDataBefore(tiempo-8);
    //ui->graficoAcX->graph(1)->removeDataBefore(tiempo-8);
    // rescale value (vertical) axis to fit the current data:
    //rafico->graph(0)->rescaleValueAxis();
    //ui->graficoAcX->graph(1)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
        grafico->yAxis->setRange(-2,2);
       grafico->xAxis->setRange(tiempo, 8, Qt::AlignRight);
      grafico->replot();
}

void Graficos::rellenarGraficos(QCustomPlot *grafico, QVector<double> X, QVector<double> Y, QString Titulo)
{
    grafico->addGraph();
    grafico->graph(0)->setData(X,Y);

    // give the axes some labels:
    grafico->xAxis->setLabel("x");
    grafico->xAxis2->setLabel(Titulo);
    grafico->yAxis->setLabel("y");

    QList<double> ordenada=Y.toList();
    qSort(ordenada.begin(),ordenada.end());

    // set axes ranges, so we see all data:
    grafico->xAxis->setRange(0, X.last());

    grafico->yAxis->setRange(ordenada.first(),ordenada.last());
    grafico->replot();
}
