TEMPLATE = lib

TARGET += ../lib/lib_adt

HEADERS += \
    visitor.h \
    ownership.h \
    object.h \
    linked_list.h \
    iterator.h \
    container.h \
    association.h \
    array.h

SOURCES += \
    visitor.cpp \
    ownership.cpp \
    object.cpp \
    iterator.cpp \
    container.cpp \
    association.cpp
