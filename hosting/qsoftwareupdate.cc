
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qsoftwareupdate.h"
#include "sdk/component.h"

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

void QSoftwareUpdate::addComponentVersion(const QString& name, int major, int minor, int patch, int serial, const QString& revId)
{
    QSoftwareVersion* componentVersion = new QSoftwareVersion;
    componentVersion->mName = name;
    componentVersion->mMajor = major;
    componentVersion->mMinor = minor;
    componentVersion->mPatch = patch;
    componentVersion->mSerial = serial;
    componentVersion->mRevId = revId;
    mComponentVersionModel->addItem(componentVersion);
}
