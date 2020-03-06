
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
        const QString propertyName = property.name();
        if (propertyName != "name" && propertyName != "objectName" && propertyName != "childNode")
        {
            QVariant propertyValue = this->property(property.name());
            switch (property.type())
            {
            case QVariant::Double: jsonObject[propertyName] = propertyValue.toDouble(); break;
            case QVariant::Int: jsonObject[propertyName] = propertyValue.toInt(); break;
            case QVariant::Bool: jsonObject[propertyName] = propertyValue.toBool(); break;
            case QVariant::String: jsonObject[propertyName] = propertyValue.toString(); break;
            default: break;
            }
        }
    }
    return jsonObject;
}

bool QJsonSyncNode::parseJsonObject(const QJsonObject& jsonObject)
{
    bool successfullyParsed = false;
    if (!jsonObject.isEmpty())
    {
        for (QJsonSyncNode* node : mList)
        {
            QString nodeName = node->objectName();
            node->parseJsonObject(jsonObject[nodeName].toObject());
        }
        const QMetaObject* metaObject = this->metaObject();
        for (int p = 0; p < metaObject->propertyCount(); ++p)
        {
            QMetaProperty property = metaObject->property(p);
            const QString propertyName = property.name();
            if (propertyName != "name" && propertyName != "objectName" && propertyName != "childNode")
            {
                QVariant propertyValue = jsonObject[propertyName].toVariant();
                setProperty(property.name(), propertyValue);
            }
        }
        successfullyParsed = true;
    }
    return successfullyParsed;
}
