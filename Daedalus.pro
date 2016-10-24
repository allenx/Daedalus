#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T16:10:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Daedalus
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ai.cpp \
    cell.cpp \
    gamefield.cpp \
    aboutpage.cpp \
    userinteractionhandler.cpp

HEADERS  += mainwindow.h \
    ai.h \
    cell.h \
    headerwrapper.h \
    gamefield.h \
    resources.h \
    aboutpage.h \
    userinteractionhandler.h

FORMS    += mainwindow.ui

CONFIG += c++11



RESOURCES += \
    resources.qrc

STATECHARTS += \
    CellStates.scxml
