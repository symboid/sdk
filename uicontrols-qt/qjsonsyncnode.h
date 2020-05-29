
#ifndef __SYMBOID_SDK_UICONTROLS_QT_QJSONSYNCNODE_H__
#define __SYMBOID_SDK_UICONTROLS_QT_QJSONSYNCNODE_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QObject>
#include "sdk/uicontrols-qt/listpropertyadapter.h"
#include <QJsonObject>

class SDK_UICONTROLS_QT_API QJsonSyncNode : public QObject, public ListPropertyAdapter<QJsonSyncNode, QJsonSyncNode> {
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "childNodes")
public:
    QJsonSyncNode(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QQmlListProperty<QJsonSyncNode> childNodes READ childNodes NOTIFY childNodesChanged)
protected:
    QQmlListProperty<QJsonSyncNode> childNodes();
signals:
    void childNodesChanged();

public:
    Q_PROPERTY(QString name READ objectName WRITE setObjectName)

protected:
    QJsonObject toJsonObject() const;
    bool parseJsonObject(const QJsonObject& jsonObject);
    virtual bool isPropertySynchronized(const QString& propertyName) const;
};

class SDK_UICONTROLS_QT_API QJsonSyncFile : public QJsonSyncNode
{
    Q_OBJECT
public:
    QJsonSyncFile(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QString filePath MEMBER mFilePath WRITE setFilePath NOTIFY filePathChanged)
protected:
    QString mFilePath;
public:
    void setFilePath(const QString& filePath);
signals:
    void filePathChanged();

public:
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();

signals:
    void loadStarted();
    void loadFinished();
    void loadFailed();

signals:
    void loadCurrent();

protected:
    bool isPropertySynchronized(const QString& propertyName) const override;
};

#endif // __SYMBOID_SDK_UICONTROLS_QT_QJSONSYNCNODE_H__
