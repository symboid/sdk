
#include "sdk/dox/setup.h"
#include "sdk/dox/document.h"
#include <QStandardPaths>
#include <QDir>
#include "sdk/arch/appqt.h"
#include "sdk/arch/log.h"

QDocument::QDocument(QObject* parent)
    : QJsonSyncFile(parent)
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

bool QDocument::existsAnother()
{
    bool exists = false;
    const QString anotherFilePath = createFilePath(mTitle);
    if (mFilePath != anotherFilePath)
    {
        QDocument anotherDocument;
        anotherDocument.setFilePath(anotherFilePath);
        exists = anotherDocument.load();
    }
    return exists;
}

bool QDocument::save()
{
    if (mTitle != "")
    {
        mFilePath = createFilePath(mTitle);
    }
    return QJsonSyncFile::save();
}

QString QDocument::createFilePath(QString documentTitle)
{
    QString filePath;
    if (documentTitle != "")
    {
        for (int t = 0, length = documentTitle.length(); t < length; ++t)
        {
            if (!documentTitle[t].isLetterOrNumber())
            {
                documentTitle[t] = '_';
            }
        }
        filePath = documentFolder() + QDir::separator() + documentTitle;

        QDir systemDocumentDir(documentFolder());
        while (systemDocumentDir.exists(filePath + sFileExtension))
        {
            filePath.push_back('_');
        }
        filePath = systemDocumentDir.absoluteFilePath(filePath + sFileExtension);
    }
    return filePath;
}

QString QDocument::documentFolder()
{
    static QString appDocFolder(arh::main_object<arh::qt_application>()->applicationName());
    static QDir sysDocDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    return sysDocDir.mkpath(appDocFolder) ? sysDocDir.absoluteFilePath(appDocFolder) : "";
}
