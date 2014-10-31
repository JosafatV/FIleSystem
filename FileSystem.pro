TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/HeaderManager/headermanager.cpp \
    src/Register/register.cpp \
    src/registerManager/registermanager.cpp \
    src/stringProcessor/decript.cpp \
    fsqlserverfilesystem.cpp \
    konstants.cpp \
    readfile.cpp \
    usefile.cpp \
    writefile.cpp

HEADERS += \
    src/HeaderManager/headermanager.h \
    src/dataStructures/Node/SimpleListNode.h \
    src/dataStructures/SimpleList.h \
    interfaceNode.h \
    ErrorCodes.h \
    src/Register/register.h \
    src/registerManager/registermanager.h \
    src/stringProcessor/decript.h \
    fsqlserverfilesystem.h \
    konstants.h \
    readfile.h \
    simpletoarr.h \
    usefile.h \
    writefile.h \
    array/array.h \
    interfaces/iData.h \
    interfaces/interfaceNode.h \
    interfaces/iPointer.h
