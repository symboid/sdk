
#include "sdk/uicontrols-qt/setup.h"
#include "sdk/uicontrols-qt/qjsonsyncnode.h"
#include <QMetaProperty>

QJsonSyncNode::QJsonSyncNode(QObject* parent)
    : QObject(parent)
{
}

QQmlListProperty<QJsonSyncNode> QJsonSyncNode::childNodes()
{
    return ListPropertyAdapter<QJsonSyncNode, QJsonSyncNode>::qmlList(this);
}

QJsonObject QJsonSyncNode::toJsonObject() const
{
    QJsonObject jsonObject;
    for (QJsonSyncNode* node : mList)
    {
        QString nodeName = node->objectName();
        jsonObject[nodeName] = node->toJsonObject();
    }
    const QMetaObject* metaObject = this->metaObject();
    for (int p = 0; p < metaObject->propertyCount(); ++p)
    {
        QMetaProperty property = metaObject->property(p);
        const char* propertyName = property.name();
        QVariant propertyValue = this->property(property.name());
        switch (property.type()) {
        case QVariant::Double: jsonObject[propertyName] = propertyValue.toDouble(); break;
        case QVariant::Int: jsonObject[propertyName] = propertyValue.toInt(); break;
        case QVariant::Bool: jsonObject[propertyName] = propertyValue.toBool(); break;
        case QVariant::String: jsonObject[propertyName] = propertyValue.toString(); break;
        default: break;
        }
    }
    return jsonObject;
}

