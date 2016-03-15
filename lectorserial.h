#ifndef LECTORSERIAL_H
#define LECTORSERIAL_H
#include <QObject>
#include <QSerialPort>
#include <QPlainTextEdit>
#include <QElapsedTimer>

class LectorSerial: public QObject
{
    Q_OBJECT


public:
    explicit LectorSerial(QObject *parent = 0);
    void readData(QSerialPort *serial, QPlainTextEdit *plainTextEdit,QString Tiempo);
    QStringList datos;
    QString dato;
    QElapsedTimer timer;

private:


public slots:
};

#endif // LECTORSERIAL_H
