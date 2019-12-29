
TARGET = sdk-network-qt
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qrestclient.cc \
    qresttablemodel.cc

HEADERS += \
    defs.h \
    init.h \
    qrestclient.h \
    qresttablemodel.h \
    setup.h

LIBS += $$moduleDep(sdk,arch)
