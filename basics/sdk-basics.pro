
TARGET=sdkbasics
BUILD_ROOT=../..
COMPONENT_NAME=sdk
include (../../build/qmake/rules.pri)

CONFIG -= core gui
CONFIG += staticlib

TEMPLATE = lib

HEADERS += \
    defs.h \
    memory.h \
    typecontexts/std_string.h \
    typecontexts/q_string.h \
    typecontexts/q_json_object.h \
    configs/$$CONTEXT/ctx/config.h \
    path.h \
    os.h \
    crypt.h \
    timecalc.h \
    system/module.h \
    system/component.h \
    system/register.h \
    contexts.h \
    stringutils.h \
    list.h \
    arccoord.h \
    frontend/tr.h \
    frontend/jsonobject.h \
    frontend/arccoord.h

INCLUDEPATH += $$PWD/../..
INCLUDEPATH += $$SYS_HOME/sdk/basics/configs/$$CONTEXT

macx {
SOURCES += \
    os_mac.mm \
    system/register_mac.mm
}
else:ios {
SOURCES += \
    os_ios.mm
}
else:win32 {
SOURCES += \
    os_win.cc \
    system/register_win.cc
}
else:android {
SOURCES += \
    os_android.cc \
    system/register_android.cc
}
else:linux {
SOURCES += \
    os_linux.cc \
    system/register_linux.cc
}

target.path = "$$OUT_PWD/../../_install/lib"
INSTALLS = target

api_headers.path = "$$INSTALL_PATH/include/sdk/basics"
api_headers.files += $$_PRO_FILE_PWD_/*.h
api_headers.files += $$_PRO_FILE_PWD_/system
api_headers.files += $$_PRO_FILE_PWD_/configs
INSTALLS += api_headers

SOURCES += \
    crypt.cc \
    timecalc.cc \
    std_string.cc \
    q_string.cc \
    q_json.cc \
    arccoord.cc \
    frontend/tr.cc \
    frontend/jsonobject.cc
