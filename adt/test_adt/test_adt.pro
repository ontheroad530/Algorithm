TEMPLATE = app

QT       -= core gui

TARGET = ../bin/adt
CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += ../lib_adt
LIBS += -L../lib -llib_adt

SOURCES += \
    main.cpp \
    test_array.cpp \
    test_list.cpp

HEADERS += \
    test_array.h \
    test_list.h
