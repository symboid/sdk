
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/document.h"
#include <QJsonDocument>
#include <QFile>

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
