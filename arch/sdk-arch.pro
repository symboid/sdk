
TARGET = sdk-arch
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    log.cc \
    mainrepo.cc \
    mod.cc \
    modmain.cc

HEADERS += \
    app.h \
    appqt.h \
    appqml.h \
    appqtw.h \
    defs.h \
    log.h \
    mod.h \
    mainobject.h \
    mainrepo.h \
    modmain.h \
    modqt.h \
    setup.h
