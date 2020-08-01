
TARGET = sdk-dox-qt
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include($${BUILD_ROOT}/sdk/build/qmake/qt-module.pri)

SOURCES += \
    document.cc \
    init.cc \
    qdocumentfoldermodel.cc \
    qdocumentlistmodel.cc \
    qrecentdoxmodel.cc

HEADERS += \
    defs.h \
    document.h \
    init.h \
    qdocumentfoldermodel.h \
    qdocumentlistmodel.h \
    qrecentdoxmodel.h \
    setup.h

RESOURCES += \
    sdk-dox-qt.qrc

LIBS += $$moduleDep(sdk,arch)
LIBS += $$moduleDep(sdk,uicontrols-qt)
