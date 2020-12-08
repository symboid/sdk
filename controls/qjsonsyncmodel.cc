
#include "sdk/controls/setup.h"
#include "sdk/controls/qjsonsyncmodel.h"

QAbstractJsonSyncModel::QAbstractJsonSyncModel(const QMetaObject& nodeMeta, QObject* parent)
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


int QAbstractJsonSyncModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return itemCount();
}

QVariant QAbstractJsonSyncModel::data(const QModelIndex& index, int role) const
{
    QVariant value;
    int itemIndex = index.row();
    if (0 <= itemIndex && itemIndex < itemCount())
    {
        if (const QJsonSyncNode* nodeItem = item(itemIndex))
        {
            const QByteArray propertyName(mRoleNames[role]);
            value = nodeItem->property(propertyName);
        }
    }
    return value;
}

bool QAbstractJsonSyncModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    bool setSuccess = false;
    int itemIndex = index.row();
    if (0 <= itemIndex && itemIndex < itemCount())
    {
        if (QJsonSyncNode* nodeItem = item(itemIndex))
        {
            const QByteArray propertyName(mRoleNames[role]);
            setSuccess = nodeItem->setProperty(propertyName, value);
        }
    }
    return setSuccess;
}

QHash<int,QByteArray> QAbstractJsonSyncModel::roleNames() const
{
    return mRoleNames;
}
