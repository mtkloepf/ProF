#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T12:41:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    machinedomain.cpp \
    domain.cpp \
    graphicsview.cpp \
    editdomain.cpp

HEADERS  += mainwindow.h \
    about.h \
    machinedomain.h \
    domain.h \
    graphicsview.h \
    editdomain.h \
    Style Document

FORMS    += mainwindow.ui \
    about.ui \
    editdomain.ui

DISTFILES += \
    StylingDocument.txt
