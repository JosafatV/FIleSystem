TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/HeaderManager/headermanager.cpp \
    src/stringProcessor/stringprocessor.cpp \
    src/registerManager/registermanager.cpp \
    src/Register/register.cpp


HEADERS += \
    src/HeaderManager/headermanager.h \
    src/stringProcessor/stringprocessor.h \
    src/registerManager/registermanager.h \
    src/Register/register.h \

    src/dataStructures/Node/SimpleListNode.h \
    src/dataStructures/SimpleList.h \
    ErrorCodes.h


