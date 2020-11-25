
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qconfig.h"
#include "sdk/hosting/qsoftwareconfig.h"

QConfigNode::QConfigNode(QObject* parent)
    : QAbstractListModel(parent)
    , mTitle("")
    , mId("")
{
}

QConfigNode::QConfigNode(const QString& id, const QString& title, QConfigNode* parentNode, const char* parentSignal)
    : QAbstractListModel(parentNode)
    , mTitle(title)
    , mId(id.toLower())
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
    roles[TitleRole] = "config_title";
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
    else if (role == TitleRole)
    {
        orbisData = subConfigNode->mTitle;
    }
    else if (role == ItemRole)
    {
        orbisData = QVariant::fromValue(const_cast<QConfigNode*>(subConfigNode));
    }
    return orbisData;
}

QString QConfigNode::configPath(const QString& parentConfigPath) const
{
    return parentConfigPath != "" ? parentConfigPath + "/" + mId : mId;
}

void QConfigNode::loadFromSettings(QSettings* settings, const QString& parentConfigPath)
{
    const QString path(configPath(parentConfigPath));
    for (QConfigNode* subConfigNode : mSubConfigs)
    {
        subConfigNode->loadFromSettings(settings, path);
    }
}

void QConfigNode::saveToSettings(QSettings* settings, const QString& parentConfigPath)
{
    const QString path(configPath(parentConfigPath));
    for (QConfigNode* subConfigNode : mSubConfigs)
    {
        subConfigNode->saveToSettings(settings, path);
    }
}

QConfigSync::QConfigSync(const QString& id, const QString& title, QConfigNode* parentNode, const char* parentSignal)
    : QConfigNode(id, title, parentNode, parentSignal)
{
    QSettings settings;
    loadFromSettings(&settings);
}

QConfigSync::~QConfigSync()
{
    QSettings settings;
    saveToSettings(&settings);
    settings.sync();
}
