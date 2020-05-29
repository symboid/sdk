
#include "sdk/uicontrols-qt/setup.h"
#include "sdk/uicontrols-qt/qjsonsyncnode.h"
#include <QMetaProperty>
#include <QJsonDocument>
#include <QFile>

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
        if (isPropertySynchronized(propertyName))
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
            if (isPropertySynchronized(propertyName))
            {
                QVariant propertyValue = jsonObject[propertyName].toVariant();
                setProperty(property.name(), propertyValue);
            }
        }
        successfullyParsed = true;
    }
    return successfullyParsed;
}

bool QJsonSyncNode::isPropertySynchronized(const QString& propertyName) const
{
    return propertyName != "name" && propertyName != "objectName" && propertyName != "childNode";
}

QJsonSyncFile::QJsonSyncFile(QObject* parent)
    : QJsonSyncNode(parent)
{
}

void QJsonSyncFile::setFilePath(const QString& filePath)
{
    if (mFilePath != filePath)
    {
        mFilePath = filePath;
        emit filePathChanged();
    }
}

bool QJsonSyncFile::load()
{
    bool loadSuccessfull = false;
    emit loadStarted();
    if (mFilePath != "")
    {
        QFile documentFile(mFilePath);
        if (documentFile.open(QIODevice::ReadOnly))
        {
            QByteArray documentBuffer = documentFile.readAll();
            QJsonDocument jsonDocument(QJsonDocument::fromJson(documentBuffer));
            if (!jsonDocument.isNull() && jsonDocument.isObject())
            {
                loadSuccessfull = parseJsonObject(jsonDocument.object());
            }
            documentFile.close();
        }
    }
    emit loadSuccessfull ? loadFinished() : loadFailed();
    return loadSuccessfull;
}

bool QJsonSyncFile::save()
{
    bool successfullySaved = false;
    if (mFilePath != "")
    {
        QJsonDocument documentToWrite(toJsonObject());
        QFile documentFile(mFilePath);
        if (documentFile.open(QIODevice::WriteOnly))
        {
            successfullySaved = (documentFile.write(documentToWrite.toJson()) != -1);
            documentFile.close();
        }
    }
    return successfullySaved;
}

bool QJsonSyncFile::isPropertySynchronized(const QString& propertyName) const
{
    return QJsonSyncNode::isPropertySynchronized(propertyName) && propertyName != "filePath";
}
