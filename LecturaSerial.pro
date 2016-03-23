    #-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T19:47:01
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LecturaSerial
TEMPLATE = app


SOURCES += main.cpp\
    qcustomplot.cpp \
    graficos.cpp \
    login.cpp \
    mainwindow.cpp


HEADERS  += \
    qcustomplot.h \
    graficos.h \
    login.h \
    mainwindow.h

FORMS    += \
    graficos.ui \
    login.ui \
    mainwindow.ui
