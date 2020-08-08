
#ifndef __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
#define __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QAbstractListModel>
#include "sdk/uicontrols-qt/qjsonsyncnode.h"
#include <QMetaProperty>
#include <QVector>

class QJsonSyncModel : public QAbstractListModel
{
public:
    QJsonSyncModel(const QMetaObject& nodeMeta, QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    int mPropertyCount;
    QHash<int,QByteArray> mRoleNames;
    QVector<QJsonSyncNode*> mItems;

public:
    void addItem(QJsonSyncNode* itemNode);
};

#endif // __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__