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
        component.cpp \
    phenomenon.cpp \
    about.cpp \
    machinedomain.cpp \
    domain.cpp \
    graphicsview.cpp

HEADERS  += mainwindow.h \
            component.h \
    phenomenon.h \
    about.h \
    machinedomain.h \
    domain.h \
    graphicsview.h

FORMS    += mainwindow.ui \
    about.ui \
    ../editdomain.ui
