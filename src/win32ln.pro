#-------------------------------------------------
#
# Project created by QtCreator 2013-04-15T01:25:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = win32ln
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controler.cpp \
    welcomewindow.cpp

HEADERS  += mainwindow.h \
    controler.h \
    welcomewindow.h

FORMS    += mainwindow.ui \
    welcomewindow.ui
