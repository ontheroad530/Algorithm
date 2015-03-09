#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T10:18:14
#
#-------------------------------------------------

QT       -= core gui

TARGET = ../lib/sort
TEMPLATE = lib

SOURCES += merge_sort.cpp

HEADERS += merge_sort.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
