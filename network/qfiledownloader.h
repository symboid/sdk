
#ifndef __SYMBOID_SDK_NETWORK_QFILEDOWNLOADER_H__
#define __SYMBOID_SDK_NETWORK_QFILEDOWNLOADER_H__

#include "sdk/network/defs.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>

class SDK_NETWORK_API QFileDownloader : public QObject
{
public:
    static constexpr const char* qml_name = "FileDownloader";

    Q_OBJECT
public:
    QFileDownloader(QObject *parent = nullptr);

public:
    Q_PROPERTY(QString downloadUrl READ downloadUrl WRITE setDownloadUrl NOTIFY downloadUrlChanged)
    QString downloadUrl() const;
    void setDownloadUrl(const QString& downloadUrl);
private:
    QString mDownloadUrl;
signals:
    void downloadUrlChanged();

public:
    Q_PROPERTY(QString localPath READ localPath NOTIFY localPathChanged)
    QString localPath() const;
private:
    QFile mLocalFile;
signals:
    void localPathChanged();

public:
    Q_PROPERTY(qreal progressPercent MEMBER mProgressPercent NOTIFY progressPercentChanged)
private:
    qreal mProgressPercent;
signals:
    void progressPercentChanged();

private:
    QScopedPointer<QNetworkAccessManager> mDownloadManager;
    QNetworkReply* mDownloadReply;
    qreal mBytesReceived;
    qreal mBytesTotal;
    bool mCanceled;
public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void cancel();
private slots:
    void onDownloadFinished();
    void onDownloadRead();
    void onDownloadError(QNetworkReply::NetworkError);
    void onDownloadProgress(qint64,qint64);

signals:
    void downloadFailed();
    void downloadCompleted();
    void downloadCanceled();
};

#endif // __SYMBOID_SDK_NETWORK_QFILEDOWNLOADER_H__
