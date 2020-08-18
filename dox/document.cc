
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

bool QDocument::save()
{
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
        mFilePath = documentFolder() + QDir::separator() + mFilePath;
        QDir systemDocumentDir(documentFolder());
        while (systemDocumentDir.exists(mFilePath + sFileExtension))
        {
            mFilePath.push_back('_');
        }
        mFilePath = systemDocumentDir.absoluteFilePath(mFilePath + sFileExtension);
    }
    return QJsonSyncFile::save();
}

QString QDocument::documentFolder()
{
    static QString appDocFolder(arh::main_object<arh::qt_application>()->applicationName());
    static QDir sysDocDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    return sysDocDir.mkpath(appDocFolder) ? sysDocDir.absoluteFilePath(appDocFolder) : "";
}
