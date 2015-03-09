#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T10:21:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ../bin/test_sort
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../sort

LIBS += -L../lib -lsort


SOURCES += main.cpp
