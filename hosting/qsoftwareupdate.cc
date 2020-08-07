
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qsoftwareupdate.h"
#include "sdk/component.h"

QSoftwareUpdate::QSoftwareUpdate(QObject* parent)
    : QObject(parent)
    , mAppVersion(new QSoftwareVersion(this))
    , mAstroVersion(new QSoftwareVersion(this))
    , mSdkVersion(new QSoftwareVersion(this))
{
    mSdkVersion->mMajor = COMPONENT_VER_MAJOR;
    mSdkVersion->mMinor = COMPONENT_VER_MINOR;
    mSdkVersion->mPatch = COMPONENT_VER_PATCH;
    mSdkVersion->mSerial = COMPONENT_VER_SERIAL;
    mSdkVersion->mRevId = COMPONENT_REV_ID;
}

bool QSoftwareUpdate::isAvailable() const
{
    return false;
}

void QSoftwareUpdate::setAppVersion(int major, int minor, int patch, int serial, const QString& revid)
{
    mAppVersion->mMajor = major;
    mAppVersion->mMinor = minor;
    mAppVersion->mPatch = patch;
    mAppVersion->mSerial = serial;
    mAppVersion->mRevId = revid;
}

QSoftwareVersion* QSoftwareUpdate::appVersion() const
{
    return mAppVersion;
}

void QSoftwareUpdate::setAstroVersion(int major, int minor, int patch, int serial, const QString& revid)
{
    mAstroVersion->mMajor = major;
    mAstroVersion->mMinor = minor;
    mAstroVersion->mPatch = patch;
    mAstroVersion->mSerial = serial;
    mAstroVersion->mRevId = revid;
}

QSoftwareVersion* QSoftwareUpdate::astroVersion() const
{
    return mAstroVersion;
}

QSoftwareVersion* QSoftwareUpdate::sdkVersion() const
{
    return mSdkVersion;
}
