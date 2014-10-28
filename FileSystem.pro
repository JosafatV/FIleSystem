TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    stringprocessor.cpp \
    src/HeaderManager/headermanager.cpp \
    src/stringProcessor/stringprocessor.cpp \
    src/registermanager.cpp \
    src/register.cpp \
    src/Register/register.cpp \
    src/registerManager/registermanager.cpp

HEADERS += \
    stringprocessor.h \
    src/HeaderManager/headermanager.h \
    src/stringProcessor/stringprocessor.h \
    src/dataStructures/Node/SimpleListNode.h \
    src/dataStructures/SimpleList.h \
    interfaceNode.h \
    src/registermanager.h \
    src/register.h \
    ErrorCodes.h \
    src/Register/register.h \
    src/registerManager/registermanager.h

