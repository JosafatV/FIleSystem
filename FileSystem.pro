TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    stringprocessor.cpp \
    src/HeaderManager/headermanager.cpp \
    src/stringProcessor/stringprocessor.cpp

HEADERS += \
    stringprocessor.h \
    src/HeaderManager/headermanager.h \
    src/stringProcessor/stringprocessor.h \
    src/dataStructures/Node/SimpleListNode.h \
    src/dataStructures/SimpleList.h \
    interfaceNode.h

