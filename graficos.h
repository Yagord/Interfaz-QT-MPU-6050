#ifndef GRAFICOS_H
#define GRAFICOS_H

#include <QMainWindow>
#include <qcustomplot.h>
//#include <ventana.h>

namespace Ui {
class Graficos;
}

class Graficos : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graficos(QWidget *parent = 0);
    ~Graficos();

public slots:
    //void Graficar(QStringList datos,QList<double> Tiempos);
    void realtimeDataSlot(QStringList linea, double tiempo);
    void inicializargraficos(QList<boolean> Checkboxes);
    void showStatusMessage(const QString &status);

signals:
    void  windowShown();

private:
    Ui::Graficos *ui;
    QStringList linea;
    double tiempo;
    QLabel *status;
    void inicializar();
    void graficartiemporealAcel(QCustomPlot *grafico,double tiempo,double dato);
    void graficartiemporealGyro(QCustomPlot *grafico,double tiempo,double dato);
    void rellenarGraficos(QCustomPlot *grafico,QVector<double> X,QVector<double> Y,QString Titulo);
};

#endif // GRAFICOS_H
