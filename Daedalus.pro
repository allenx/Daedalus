#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T16:10:34
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Daedalus
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.12

SOURCES += main.cpp\
        mainwindow.cpp \
    ai.cpp \
    cell.cpp \
    gamefield.cpp \
    aboutpage.cpp \
    userinteractionhandler.cpp \
    soundhandler.cpp \
    preferences.cpp \
    winningdialog.cpp \
    defeateddialog.cpp \
    stopwatch.cpp \
    adobeocrlabel.cpp

HEADERS  += mainwindow.h \
    ai.h \
    cell.h \
    headerwrapper.h \
    gamefield.h \
    resources.h \
    aboutpage.h \
    userinteractionhandler.h \
    soundhandler.h \
    preferences.h \
    winningdialog.h \
    defeateddialog.h \
    stopwatch.h \
    adobeocrlabel.h

FORMS    += mainwindow.ui

CONFIG += c++11



RESOURCES += \
    resources.qrc

STATECHARTS += \
    CellStates.scxml


