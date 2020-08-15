
#ifndef __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
#define __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QAbstractListModel>
#include "sdk/uicontrols-qt/qjsonsyncnode.h"
#include <QMetaProperty>
#include <QVector>

class SDK_UICONTROLS_QT_API QAbstractJsonSyncModel : public QAbstractListModel
{
protected:
    QAbstractJsonSyncModel(const QMetaObject& nodeMeta, QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    int mPropertyCount;
    QHash<int,QByteArray> mRoleNames;

private:
    virtual int itemCount() const = 0;
    virtual const QJsonSyncNode* item(int itemIndex) const = 0;
};

template <class JsonSyncNode>
class SDK_UICONTROLS_QT_API QJsonSyncModel : public QAbstractJsonSyncModel
{
public:
    QJsonSyncModel(QObject* parent)
        : QAbstractJsonSyncModel(JsonSyncNode::staticMetaObject, parent)
    {
    }

protected:
    typedef QVector<JsonSyncNode*> Items;
    Items mItems;

private:
    int itemCount() const override { return  mItems.size(); }
    const QJsonSyncNode* item(int itemIndex) const override { return mItems.at(itemIndex); }

public:
    void addItem(JsonSyncNode* itemNode)
    {
        if (itemNode != nullptr)
        {
            itemNode->setParent(this);
            mItems.push_back(itemNode);
        }
    }

    void clearItems()
    {
        for (JsonSyncNode* item : mItems)
        {
            item->deleteLater();
        }
        mItems.clear();
    }
};

#endif // __SYMBOID_SD_UICONTROLS_QT_QJSONSYNCMODEL_H__
