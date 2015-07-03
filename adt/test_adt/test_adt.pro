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
    test_list.cpp \
    test_stack.cpp \
    test_queue.cpp \
    test_hash_table.cpp \
    test_tree.cpp \
    test_priority.cpp

HEADERS += \
    test_array.h \
    test_list.h \
    test_stack.h \
    test_queue.h \
    test_hash_table.h \
    test_tree.h \
    test_priority.h
