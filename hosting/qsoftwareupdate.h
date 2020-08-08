
#ifndef __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__
#define __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__

#include "sdk/hosting/defs.h"
#include <QObject>
#include "sdk/arch/mainobject.h"
#include "sdk/uicontrols-qt/qjsonsyncmodel.h"

class QSoftwareVersion : public QJsonSyncNode
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
    Q_PROPERTY(QAbstractListModel* componentVersions MEMBER mComponentVersionModel CONSTANT)
private:
    QJsonSyncModel* mComponentVersionModel;
public:
    void addComponentVersion(const QString& name, int major, int minor, int patch, int serial, const QString& revId);
};

#endif // __SYMBOID_SDK_HOSTING_QSOFTWAREUPDATE_H__