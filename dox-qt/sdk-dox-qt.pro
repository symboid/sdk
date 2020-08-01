
TARGET = sdk-dox-qt
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
    setup.h

LIBS += $$moduleDep(sdk,uicontrols-qt)
LIBS += $$moduleDep(sdk,arch)

RESOURCES += \
    sdk-dox-qt.qrc
