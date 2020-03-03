
#ifndef __SYMBOID_SDK_UICONTROLS_QT_QJSONSYNCNODE_H__
#define __SYMBOID_SDK_UICONTROLS_QT_QJSONSYNCNODE_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QObject>
#include "sdk/uicontrols-qt/listpropertyadapter.h"
#include <QJsonObject>

class QJsonSyncNode : public QObject, public ListPropertyAdapter<QJsonSyncNode, QJsonSyncNode> {
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
    Q_PROPERTY(QString name WRITE setObjectName)

protected:
    QJsonObject toJsonObject() const;
};

#endif // __SYMBOID_SDK_UICONTROLS_QT_QJSONSYNCNODE_H__