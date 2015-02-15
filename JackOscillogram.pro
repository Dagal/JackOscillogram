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
    QJackOscillogram.cpp \
    CJackClient.cpp \
    IJackClient.cpp \
    CJackPort.cpp \
    IJackPort.cpp \
    CJackPortAudioIn.cpp \
    CJackPortAudioOut.cpp \
    CJackPortMidiIn.cpp \
    CJackPortMidiOut.cpp \
    IJackPortAudioIn.cpp \
    IJackPortAudioOut.cpp \
    IJackPortMidiIn.cpp \
    IJackPortMidiOut.cpp

HEADERS  += MainWindow.h \
    QJackOscillogram.h \
    CJackClient.h \
    IJackClient.h \
    CJackPort.h \
    IJackPort.h \
    CJackPortAudioIn.h \
    CJackPortAudioOut.h \
    CJackPortMidiIn.h \
    CJackPortMidiOut.h \
    IJackPortAudioIn.h \
    IJackPortAudioOut.h \
    IJackPortMidiIn.h \
    IJackPortMidiOut.h

DISTFILES += \
    Doxyfile
