
#ifndef __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__
#define __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__

#include "sdk/hosting/defs.h"
#include <QObject>
#include "sdk/arch/mainobject.h"
#include "sdk/controls/qjsonsyncmodel.h"

class SDK_HOSTING_API QSoftwareVersion : public QJsonSyncNode
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "SoftwareVersion";

    QSoftwareVersion(QObject* parent = Q_NULLPTR)
        : QJsonSyncNode(parent)
    {
    }

    Q_PROPERTY(QString name MEMBER mName CONSTANT)
    QString mName;

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
    QML_SINGLETON_OBJECT(SoftwareUpdate)

public:
    QSoftwareUpdate(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(bool available READ isAvailable NOTIFY availableChanged)
private:
    bool isAvailable() const;
signals:
    void availableChanged();

public:
    Q_PROPERTY(QAbstractListModel* componentVersions MEMBER mComponentVersionModel CONSTANT)
private:
    QJsonSyncModel<QSoftwareVersion>* mComponentVersionModel;
public:
    QSoftwareVersion* addComponentVersion(const QString& name, int major, int minor, int patch, int serial, const QString& revId);

public:
    Q_PROPERTY(QSoftwareVersion* appVersion READ appVersion CONSTANT)
    QSoftwareVersion* appVersion();
private:
    QSoftwareVersion* mAppVersion = nullptr;
public:
    void setAppVersion(const QString& name, int major, int minor, int patch, int serial, const QString& revId);

public:
    Q_PROPERTY(int appSwid MEMBER mAppSwid CONSTANT)
public:
    int mAppSwid = 0;

public:
    Q_PROPERTY(QString platform READ platform CONSTANT)
public:
    QString platform() const;

public:
    Q_INVOKABLE bool execUpdater(const QString& installerFilePath);
};

#endif // __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__
