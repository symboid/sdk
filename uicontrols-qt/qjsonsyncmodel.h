
#ifndef __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
#define __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QAbstractListModel>
#include "sdk/uicontrols-qt/qjsonsyncnode.h"
#include <QMetaProperty>
#include <QVector>

class SDK_UICONTROLS_QT_API QJsonSyncModel : public QAbstractListModel
{
public:
    QJsonSyncModel(const QMetaObject& nodeMeta, QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

protected:
    int mPropertyCount;
    QHash<int,QByteArray> mRoleNames;
    typedef QVector<QJsonSyncNode*> Items;
    Items mItems;

public:
    void addItem(QJsonSyncNode* itemNode);
    void clearItems();
};

#endif // __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
