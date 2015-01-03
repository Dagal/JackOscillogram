#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T17:39:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JackOscillogram
TEMPLATE = app

LIBS += -ljack

SOURCES += main.cpp\
				MainWindow.cpp \
    QJackOscillogram.cpp

HEADERS  += MainWindow.h \
    QJackOscillogram.h
