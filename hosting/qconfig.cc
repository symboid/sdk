
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qconfig.h"
#include "sdk/hosting/qsoftwareconfig.h"

QAbstractConfig::QAbstractConfig(QObject* parent)
    : QAbstractListModel(parent)
    , mId("")
{
}

QAbstractConfig::QAbstractConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal)
    : QAbstractListModel(parentNode)
    , mId(id.toLower())
{
    if (parentNode != nullptr)
    {
        connect(this, SIGNAL(changed()), parentNode, SIGNAL(changed()));
        if (parentSignal != nullptr)
        {
            connect(this, SIGNAL(changed()), parentNode, parentSignal);
        }
    }
}

QHash<int, QByteArray> QAbstractConfig::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[ValueRole] = "config_value";
    roles[ItemRole] = "config_item";
    return roles;
}

int QAbstractConfig::rowCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return subConfigCount();
}

QVariant QAbstractConfig::data(const QModelIndex& index, int role) const
{
    QVariant orbisData;
    const QAbstractConfig* subConfigNode = subConfig(index.row());
    if (subConfigNode == nullptr)
    {
    }
    else if (role == ValueRole)
    {
        orbisData = subConfigNode->value();
    }
    else if (role == ItemRole)
    {
        orbisData = QVariant::fromValue(const_cast<QAbstractConfig*>(subConfigNode));
    }
    return orbisData;
}

QString QAbstractConfig::configPath(const QString& parentConfigPath) const
{
    return parentConfigPath != "" ? parentConfigPath + "/" + mId : mId;
}

void QAbstractConfig::loadFromSettings(QSettings* settings, const QString& parentConfigPath)
{
    const QString path(configPath(parentConfigPath));
    for (int c = 0, cCount = subConfigCount(); c < cCount; ++c)
    {
        subConfig(c)->loadFromSettings(settings, path);
    }
}

void QAbstractConfig::saveToSettings(QSettings* settings, const QString& parentConfigPath)
{
    const QString path(configPath(parentConfigPath));
    for (int c = 0, cCount = subConfigCount(); c < cCount; ++c)
    {
        subConfig(c)->saveToSettings(settings, path);
    }
}

