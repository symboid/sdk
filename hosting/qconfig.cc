
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qconfig.h"
#include "sdk/hosting/qsoftwareconfig.h"

QConfigNode::QConfigNode()
    : QAbstractListModel(nullptr)
    , mName("")
{
}

QConfigNode::QConfigNode(const QString& name, QConfigNode* parentNode, const char* parentSignal)
    : QAbstractListModel(parentNode)
    , mName(name)
{
    if (parentNode != nullptr)
    {
        parentNode->mSubConfigs.push_back(this);
        connect(this, SIGNAL(changed()), parentNode, SIGNAL(changed()));
        if (parentSignal != nullptr)
        {
            connect(this, SIGNAL(changed()), parentNode, parentSignal);
        }
    }
}

int QConfigNode::subConfigCount() const
{
    return mSubConfigs.size();
}

const QConfigNode* QConfigNode::subConfig(int index) const
{
    return 0 <= index && index < mSubConfigs.size() ? mSubConfigs[index] : nullptr;
}

QConfigNode* QConfigNode::subConfig(int index)
{
    return 0 <= index && index < mSubConfigs.size() ? mSubConfigs[index] : nullptr;
}

QHash<int, QByteArray> QConfigNode::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "config_name";
    roles[ValueRole] = "config_value";
    roles[ItemRole] = "config_item";
    return roles;
}

int QConfigNode::rowCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return subConfigCount();
}

QVariant QConfigNode::data(const QModelIndex& index, int role) const
{
    QVariant orbisData;
    const QConfigNode* subConfigNode = subConfig(index.row());
    if (subConfigNode == nullptr)
    {
    }
    else if (role == ValueRole)
    {
        orbisData = subConfigNode->value();
    }
    else if (role == NameRole)
    {
        orbisData = subConfigNode->mName;
    }
    else if (role == ItemRole)
    {
        orbisData = QVariant::fromValue(const_cast<QConfigNode*>(subConfigNode));
    }
    return orbisData;
}
