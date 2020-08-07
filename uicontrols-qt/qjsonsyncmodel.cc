
#include "sdk/uicontrols-qt/setup.h"
#include "sdk/uicontrols-qt/qjsonsyncmodel.h"

QJsonSyncModel::QJsonSyncModel(QObject* parent)
    : QAbstractListModel(parent)
    , mRoleNames(QAbstractListModel::roleNames())
{
}

bool QJsonSyncModel::initModel(QJsonSyncNode* masterNode)
{
    bool initSuccess = false;
    if (masterNode != nullptr)
    {

    }
    return initSuccess;
}

int QJsonSyncModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}

QVariant QJsonSyncModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}

QHash<int,QByteArray> QJsonSyncModel::roleNames() const
{
    return mRoleNames;
}
