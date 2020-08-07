
#ifndef __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__
#define __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__

#include "sdk/hosting/defs.h"
#include <QObject>
#include "sdk/arch/mainobject.h"

class QSoftwareVersion : public QObject
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "SoftwareVersion";

    QSoftwareVersion(QObject* parent = Q_NULLPTR)
        : QObject(parent)
    {
    }

    Q_PROPERTY(int major MEMBER mMajor CONSTANT)
    int mMajor;

    Q_PROPERTY(int minor MEMBER mMinor CONSTANT)
    int mMinor;

    Q_PROPERTY(int patch MEMBER mPatch CONSTANT)
    int mPatch;

    Q_PROPERTY(int serial MEMBER mSerial CONSTANT)
    int mSerial;

    Q_PROPERTY(QString revid MEMBER mRevId CONSTANT)
    QString mRevId;
};

class SDK_HOSTING_API QSoftwareUpdate : public QObject
{
    Q_OBJECT
    QML_SINGLETON(SoftwareUpdate)

public:
    QSoftwareUpdate(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(bool available READ isAvailable NOTIFY availableChanged)
private:
    bool isAvailable() const;
signals:
    void availableChanged();

public:
    Q_PROPERTY(QSoftwareVersion* appVersion READ appVersion CONSTANT)
    void setAppVersion(int major, int minor, int patch, int serial, const QString& revId);
    QSoftwareVersion* appVersion() const;
private:
    QSoftwareVersion* mAppVersion;

public:
    Q_PROPERTY(QSoftwareVersion* astroVersion READ astroVersion CONSTANT)
    void setAstroVersion(int major, int minor, int patch, int serial, const QString& revId);
    QSoftwareVersion* astroVersion() const;
private:
    QSoftwareVersion* mAstroVersion;

public:
    Q_PROPERTY(QSoftwareVersion* sdkVersion READ sdkVersion CONSTANT)
    QSoftwareVersion* sdkVersion() const;
private:
    QSoftwareVersion* mSdkVersion;
};

#endif // __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__
