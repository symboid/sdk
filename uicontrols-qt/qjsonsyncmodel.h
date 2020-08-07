
#ifndef __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
#define __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QAbstractListModel>
#include "sdk/uicontrols-qt/qjsonsyncnode.h"

class QJsonSyncModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QJsonSyncModel(QObject* parent = Q_NULLPTR);
    bool initModel(QJsonSyncNode* masterNode);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    QHash<int,QByteArray> mRoleNames;
};

#endif // __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
