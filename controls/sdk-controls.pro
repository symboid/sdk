
TARGET = sdk-controls
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qinputoperation.cc \
    qjsonsyncmodel.cc \
    qjsonsyncnode.cc \
    qunixtimeconverter.cc

HEADERS += \
    defs.h \
    init.h \
    listpropertyadapter.h \
    qinputoperation.h \
    qjsonsyncmodel.h \
    qjsonsyncnode.h \
    qunixtimeconverter.h \
    setup.h

RESOURCES += \
    sdk-controls.qrc

LIBS += $$moduleDep(sdk,arch)
