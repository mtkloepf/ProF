#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T12:41:20
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS_WARN_OFF += -Wno-unused-parameter
CONFIG += warn_off

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    machinedomain.cpp \
    domain.cpp \
    graphicsview.cpp \
    editdomain.cpp \
    interface.cpp \
    editinterface.cpp \
    editphenomenon.cpp \
    phenomenon.cpp \
    contextdata.cpp \
    editsharedphenomenon.cpp \
    requirement.cpp \
    problemdata.cpp \
    editrequirement.cpp

HEADERS  += mainwindow.h \
    about.h \
    machinedomain.h \
    domain.h \
    graphicsview.h \
    editdomain.h \
    Style Document \
    interface.h \
    editinterface.h \
    editphenomenon.h \
    phenomenon.h \
    contextdata.h \
    editsharedphenomenon.h \
    requirement.h \
    problemdata.h \
    editrequirement.h

FORMS    += mainwindow.ui \
    about.ui \
    editdomain.ui \
    editinterface.ui \
    editphenomenon.ui \
    editsharedphenomenon.ui \
    editrequirement.ui

DISTFILES += \
    StylingDocument.txt
