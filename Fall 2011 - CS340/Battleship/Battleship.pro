#-------------------------------------------------
#
# Project created by QtCreator 2011-11-22T13:04:40
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = Battleship
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    gridbutton.cpp \
    board.cpp \
    square.cpp \
    gameinfo.cpp

HEADERS  += mainwindow.h \
    gridbutton.h \
    square.h \
    board.h \
    gameinfo.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

















