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
    array.h \
    stack.h \
    queue.h \
    list.h \
    hash_table.h \
    tree.h

SOURCES += \
    visitor.cpp \
    ownership.cpp \
    object.cpp \
    iterator.cpp \
    container.cpp \
    association.cpp \
    stack.cpp \
    queue.cpp \
    list.cpp \
    hash_table.cpp \
    tree.cpp
