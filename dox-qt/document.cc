
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/document.h"
#include <QDebug>
#include <QMetaProperty>

QDocumentNode::QDocumentNode(QObject* parent)
    : QObject(parent)
{
}

QQmlListProperty<QDocumentNode> QDocumentNode::childNodes()
{
    return ListProperty<QDocumentNode, QDocumentNode>::qmlList(this);
}

QJsonObject QDocumentNode::toJsonObject() const
{
    QJsonObject jsonObject;
    for (QDocumentNode* node : mList)
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

QDocument::QDocument(QObject* parent)
    : QDocumentNode(parent)
{
}

void QDocument::setTitle(const QString& title)
{
    if (mTitle != title)
    {
        mTitle = title;
        emit titleChanged();
    }
}

void QDocument::save()
{
    QJsonObject documentObject = toJsonObject();
    QJsonObject dd = documentObject;
}
