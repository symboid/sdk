
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qconfig.h"
#include "sdk/hosting/qsoftwareconfig.h"

QConfigNode::QConfigNode(QObject* parent)
    : QObject(parent)
{
}

void QConfigNode::setPropertyModified(const QString& propertyName, bool isModified)
{
}

bool QConfigNode::isPropertyModified(const QString& propertyName) const
{
    return false;
}

QConfig::QConfig(QObject* parent)
    : QConfigNode(parent)
{
}

QQmlListProperty<QConfigNode> QConfig::subConfigs()
{
    return ListPropertyAdapter<QConfig, QConfigNode>::qmlList(this);
}

void QConfig::addSubConfig(QConfigNode* subConfig)
{
    mList.push_back(subConfig);
}
