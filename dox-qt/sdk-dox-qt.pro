
TARGET = sdk-dox-qt
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    document.cc \
    init.cc

HEADERS += \
    defs.h \
    document.h \
    init.h \
    setup.h

LIBS += $$moduleDep(sdk,arch)
LIBS += $$moduleDep(sdk,uicontrols-qt)

RESOURCES += \
    sdk-dox-qt.qrc
