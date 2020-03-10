
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/document.h"
#include <QJsonDocument>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

QDocument::QDocument(QObject* parent)
    : QDocumentNode(parent)
{
}

QString QDocument::title() const
{
    return mTitle;
}

void QDocument::setTitle(const QString& title)
{
    if (mTitle != title)
    {
        mTitle = title;
        emit titleChanged();
    }
}

void QDocument::setFilePath(const QString& filePath)
{
    if (mFilePath != filePath)
    {
        mFilePath = filePath;
        emit filePathChanged();
    }
}

bool QDocument::load()
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

bool QDocument::save()
{
    bool successfullySaved = false;
    if (mFilePath == "" && mTitle != "")
    {
        for (QChar t : mTitle)
        {
            QChar lower(t.toLower());
            if ('a' <= lower && lower <= 'z')
            {
                mFilePath.push_back(t);
            }
            else if ('0' <= lower && lower <= '9')
            {
                mFilePath.push_back(lower);
            }
            else
            {
                mFilePath.push_back('_');
            }
        }
        mFilePath = systemFolder() + QDir::separator() + mFilePath;
        QDir systemDocumentDir(systemFolder());
        while (systemDocumentDir.exists(mFilePath + sFileExtension))
        {
            mFilePath.push_back('_');
        }
        mFilePath = systemDocumentDir.absoluteFilePath(mFilePath + sFileExtension);
    }
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

QString QDocument::systemFolder()
{
    QString systemDocuments = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    return systemDocuments;
}

bool QDocument::isPropertySynchronized(const QString& propertyName) const
{
    return QJsonSyncNode::isPropertySynchronized(propertyName) && propertyName != "filePath";
}
