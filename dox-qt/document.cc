
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/document.h"

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
