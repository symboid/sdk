
TARGET = sdk-hosting
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qconfig.cc \
    qsoftwareconfig.cc \
    qsoftwareupdate.cc

HEADERS += \
    defs.h \
    init.h \
    qconfig.h \
    qsoftwareconfig.h \
    qsoftwareupdate.h \
    setup.h

RESOURCES += \
    sdk-hosting.qrc

LIBS += $$moduleDep(sdk,arch)
LIBS += $$moduleDep(sdk,uicontrols-qt)
LIBS += $$moduleDep(sdk,network-qt)
