
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qsoftwareupdate.h"
#include "sdk/component.h"
#include <QProcess>

QSoftwareUpdate::QSoftwareUpdate(QObject* parent)
    : QObject(parent)
    , mComponentVersionModel(new QJsonSyncModel<QSoftwareVersion>(this))
{
    addComponentVersion(COMPONENT_NAME, COMPONENT_VER_MAJOR, COMPONENT_VER_MINOR,
                        COMPONENT_VER_PATCH, COMPONENT_VER_SERIAL, COMPONENT_REV_ID);
}

bool QSoftwareUpdate::isAvailable() const
{
    return false;
}

QSoftwareVersion* QSoftwareUpdate::addComponentVersion(const QString& name, int major, int minor, int patch, int serial, const QString& revId)
{
    QSoftwareVersion* componentVersion = new QSoftwareVersion;
    componentVersion->mName = name;
    componentVersion->mMajor = major;
    componentVersion->mMinor = minor;
    componentVersion->mPatch = patch;
    componentVersion->mSerial = serial;
    componentVersion->mRevId = revId;
    mComponentVersionModel->addItem(componentVersion);
    return componentVersion;
}

void QSoftwareUpdate::setAppVersion(const QString& name, int major, int minor, int patch, int serial, const QString& revId)
{
    mAppVersion = addComponentVersion(name, major, minor, patch, serial, revId);
}

QSoftwareVersion* QSoftwareUpdate::appVersion()
{
    static QSoftwareVersion* emptyVersion = new QSoftwareVersion(this);
    return mAppVersion != nullptr ? mAppVersion : emptyVersion;
}

QString QSoftwareUpdate::platform() const
{
#if defined Q_OS_WIN64
    return "win_x64";
#elif defined Q_OS_WIN32
    return "win_x86";
#elif defined Q_OS_ANDROID
    return "android";
#elif defined Q_OS_WASM
    return "wasm_32";
#elif defined Q_OS_LINUX
    return "linux";
#elif defined Q_OS_MACOS
    return "macos";
#elif defined Q_OS_IOS
    return "ios";
#else
    return "???";
#endif
}

bool QSoftwareUpdate::execUpdater(const QString& installerFilePath)
{
    bool startSuccess = false;
#ifndef Q_OS_IOS
    QProcess* updateProcess = new QProcess(this);
    updateProcess->setProgram(installerFilePath);
#if defined Q_OS_WIN
    updateProcess->setArguments({"--autorun:1"});
#endif
    startSuccess = updateProcess->startDetached();
    updateProcess->deleteLater();
#endif
    return startSuccess;
}
