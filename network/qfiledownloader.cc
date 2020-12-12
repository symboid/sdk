
#include "sdk/network/setup.h"
#include "sdk/network/qfiledownloader.h"
#include <QDir>
#include <QDebug>

QFileDownloader::QFileDownloader(QObject* parent)
    : QObject(parent)
    , mProgressPercent(0.0)
    , mDownloadManager(new QNetworkAccessManager)
    , mDownloadReply(nullptr)
{
}

QString QFileDownloader::downloadUrl() const
{
    return mDownloadUrl;
}

void QFileDownloader::setDownloadUrl(const QString& downloadUrl)
{
    if (mDownloadUrl != downloadUrl)
    {
        mDownloadUrl = downloadUrl;
        emit downloadUrlChanged();

        const QString fileName = downloadUrl.mid(downloadUrl.lastIndexOf('/') + 1);
        mLocalFile.setFileName(QDir::tempPath() + QDir::separator() + fileName);
        emit localPathChanged();
    }
}

QString QFileDownloader::localPath() const
{
    return mLocalFile.fileName();
}

void QFileDownloader::start()
{
    mBytesReceived = 0;
    mBytesTotal = 0;
    mCanceled = false;

    if (!mLocalFile.open(QFile::WriteOnly))
    {
        qCritical() << "Local file" << localPath() << "cannot be created!";
        emit downloadFailed();
    }
    else if (!(mDownloadReply = mDownloadManager->get(QNetworkRequest(mDownloadUrl))))
    {
        qCritical() << "Download url" << mDownloadUrl << "cannot be accessed!";
    }
    else
    {
        connect(mDownloadReply, SIGNAL(finished()), this, SLOT(onDownloadFinished()));
        connect(mDownloadReply, SIGNAL(readyRead()), this, SLOT(onDownloadRead()));
        connect(mDownloadReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onDownloadError(QNetworkReply::NetworkError)));
        connect(mDownloadReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
        qInfo() << "Download url" << mDownloadUrl << "successfully opened. Local path is" << mLocalFile.fileName();
    }
}

void QFileDownloader::cancel()
{
    if (mDownloadReply)
    {
        mCanceled = true;
        mDownloadReply->abort();
    }
}

void QFileDownloader::onDownloadFinished()
{
    mLocalFile.close();
    if (!mDownloadReply || mDownloadReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
    {
        mLocalFile.remove();

        mBytesReceived = 0;
        mBytesReceived = 0;
        mProgressPercent = 0;
        emit progressPercentChanged();

        qCritical() << "Download of" << mDownloadUrl << "failed!";
        emit downloadFailed();
    }
    else if (mCanceled)
    {
        mLocalFile.remove();
        qInfo() << "Download of" << mDownloadUrl << "aborted.";
        emit downloadCanceled();
    }
    else
    {
        qInfo() << "Download of" << mDownloadUrl << "successfully completed.";
        emit downloadCompleted();
    }
    mDownloadReply->deleteLater();
    mDownloadReply = nullptr;
}

void QFileDownloader::onDownloadRead()
{
    if (mDownloadReply)
    {
        mLocalFile.write(mDownloadReply->readAll());
    }
}

void QFileDownloader::onDownloadError(QNetworkReply::NetworkError networkError)
{
    qWarning() << "Download of" << mDownloadUrl << "run to error! Error =" << networkError;
    if (mDownloadReply)
    {
        mDownloadReply->close();
    }
    emit downloadFailed();
}

void QFileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    mBytesReceived = bytesReceived;
    mBytesTotal = bytesTotal;
    mProgressPercent = bytesTotal ? qreal(bytesReceived) / qreal(bytesTotal) : 0.0;
    emit progressPercentChanged();
}
