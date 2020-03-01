
TARGET = sdk-uicontrols-qt
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qinputoperation.cc \
    qjsonsyncnode.cc \
    qunixtimeconverter.cc

HEADERS += \
    defs.h \
    init.h \
    listpropertyadapter.h \
    qinputoperation.h \
    qjsonsyncnode.h \
    qunixtimeconverter.h \
    setup.h

RESOURCES += \
    sdk-uicontrols-qt.qrc

LIBS += $$moduleDep(sdk,arch)
