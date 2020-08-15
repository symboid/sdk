
#include "sdk/uicontrols-qt/setup.h"
#include "sdk/uicontrols-qt/qjsonsyncmodel.h"

QJsonSyncModel::QJsonSyncModel(const QMetaObject& nodeMeta, QObject* parent)
    : QAbstractListModel(parent)
    , mPropertyCount(nodeMeta.propertyCount() - nodeMeta.propertyOffset())
    , mRoleNames(QAbstractListModel::roleNames())
{
    int propertyOffset = nodeMeta.propertyOffset();
    for (int p = 0; p < mPropertyCount; ++p)
    {
        const QMetaProperty property = nodeMeta.property(propertyOffset + p);
        QString pName(property.name());
        mRoleNames[Qt::UserRole + p] = QByteArray(property.name());
    }
}


int QJsonSyncModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return mItems.size();
}

QVariant QJsonSyncModel::data(const QModelIndex& index, int role) const
{
    QVariant value;
    int itemIndex = index.row();
    if (0 <= itemIndex && itemIndex < mItems.size())
    {
        if (const QJsonSyncNode* nodeItem = mItems[itemIndex])
        {
            const QByteArray propertyName(mRoleNames[role]);
            value = nodeItem->property(propertyName);
        }

    }
    return value;
}

QHash<int,QByteArray> QJsonSyncModel::roleNames() const
{
    return mRoleNames;
}

void QJsonSyncModel::addItem(QJsonSyncNode* itemNode)
{
    if (itemNode != nullptr)
    {
        itemNode->setParent(this);
        mItems.push_back(itemNode);
    }
}

void QJsonSyncModel::clearItems()
{
    for (QJsonSyncNode* item : mItems)
    {
        item->deleteLater();
    }
    mItems.clear();
}
