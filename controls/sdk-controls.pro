
TARGET = sdk-controls
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qcalctask.cc \
    qcalcthread.cc \
    qjsonsyncmodel.cc \
    qjsonsyncnode.cc \
    qunixtimeconverter.cc

HEADERS += \
    defs.h \
    init.h \
    listpropertyadapter.h \
    qcalctask.h \
    qcalcthread.h \
    qjsonsyncmodel.h \
    qjsonsyncnode.h \
    qunixtimeconverter.h \
    setup.h

RESOURCES += \
    sdk-controls.qrc

LIBS += $$moduleDep(sdk,arch)
