
TARGET = sdk-network-qt
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qrestclient.cc \
    qrestmodel.cc \
    qrestobjectmodel.cc \
    qresttablemodel.cc

HEADERS += \
    defs.h \
    init.h \
    qrestclient.h \
    qrestmodel.h \
    qrestobjectmodel.h \
    qresttablemodel.h \
    setup.h

LIBS += $$moduleDep(sdk,arch)
