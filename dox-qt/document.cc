
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/document.h"
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

QString QDocument::ensureAppDocDir(const QDir& sysDocDir)
{
    arh::main_object<arh::qt_application> application;
    static QString appDocFolder(application->applicationName());
    QString appDocDir;
    if (sysDocDir.exists())
    {
        if (!sysDocDir.exists(appDocFolder))
        {
            sysDocDir.mkdir(appDocFolder);
        }
        appDocDir = sysDocDir.absoluteFilePath(appDocFolder);
    }
    log_info << "Documents folder = '"<< appDocDir << "'";
    return appDocDir;
}

QString QDocument::documentFolder()
{
    static QDir sysDocDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    static QString appDocDir = sysDocDir.exists() ? ensureAppDocDir(sysDocDir) : "";
    return appDocDir;
}
