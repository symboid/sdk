
TARGET = sdk-uicontrols-qt
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    init.cc

HEADERS += \
    defs.h \
    init.h \
    setup.h

RESOURCES += \
    sdk-uicontrols-qt.qrc

LIBS += $$moduleDep(sdk,arch)
