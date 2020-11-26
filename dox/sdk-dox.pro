
TARGET = sdk-dox
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    document.cc \
    init.cc \
    qdocumentfoldermodel.cc

HEADERS += \
    defs.h \
    document.h \
    init.h \
    qdocumentfoldermodel.h \
    qdocumentlistmodel.h \
    setup.h

RESOURCES += \
    sdk-dox.qrc

LIBS += $$moduleDep(sdk,arch)
LIBS += $$moduleDep(sdk,controls)
