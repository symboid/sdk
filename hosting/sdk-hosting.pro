
TARGET = sdk-hosting
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/build/qmake/qt-module.pri)

SOURCES += \
    init.cc \
    qappconfig.cc \
    qconfig.cc \
    qsoftwareconfig.cc \
    qsoftwareupdate.cc \
    quiconfig.cc

HEADERS += \
    defs.h \
    init.h \
    qappconfig.h \
    qconfig.h \
    qsoftwareconfig.h \
    qsoftwareupdate.h \
    quiconfig.h \
    setup.h

RESOURCES += \
    sdk-hosting.qrc

LIBS += $$moduleDep(sdk,arch)
LIBS += $$moduleDep(sdk,controls)
LIBS += $$moduleDep(sdk,network)
