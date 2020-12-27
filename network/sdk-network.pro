
TARGET = sdk-network
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qfiledownloader.cc \
    qrestclient.cc \
    qrestmodel.cc \
    qrestobjectmodel.cc \
    qresttablemodel.cc

HEADERS += \
    defs.h \
    init.h \
    qfiledownloader.h \
    qrestclient.h \
    qrestmodel.h \
    qrestobjectmodel.h \
    qresttablemodel.h \
    setup.h

LIBS += $$moduleDep(sdk,arch)
