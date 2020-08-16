
#include "sdk/network/setup.h"
#include "sdk/network/qrestclient.h"
#include <QNetworkReply>

QRestCaller::QRestCaller(QObject* parent)
    : QObject(parent)
    , mReply(Q_NULLPTR)
    , mStatus(QNetworkReply::NoError)
    , mIsResultCompact(false)
{
}

void QRestCaller::setReply(QNetworkReply* reply)
{
    if (reply)
    {
        mReply = reply;
        connect(mReply, SIGNAL(finished()), this, SLOT(onFinished()));
        connect(mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        connect(mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
    }
    else
    {
        disconnect(mReply, SIGNAL(finished()), this, SLOT(onFinished()));
        disconnect(mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        disconnect(mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
        emit mReply->deleteLater();
        mReply = Q_NULLPTR;
    }
}

void QRestCaller::onFinished()
{
    if (mReply != Q_NULLPTR && mReply->error() == QNetworkReply::NoError)
    {
        mStatus = QNetworkReply::NoError;
        emit beginUpdateResult();
        fetchResult(mReply);
        emit endUpdateResult();
    }
    else
    {
        mStatus = QNetworkReply::UnknownNetworkError;
    }
    emit endUpdate();
}

void QRestCaller::onError(QNetworkReply::NetworkError error)
{
    mStatus = error;
    emit endUpdate();
}

void QRestCaller::setResultCompact(bool isResultCompact)
{
    mIsResultCompact = isResultCompact;
}

QRestClient::QRestClient(QObject* parent)
    : QNetworkAccessManager(parent)
{
}

void QRestClient::setApiAddress(const QUrl& apiAddress)
{
    if (mApiAddress != apiAddress)
    {
        mApiAddress = apiAddress;
        emit apiAddressChanged();
    }
}

void QRestClient::setAuthUser(const QString& authUser)
{
    if (mAuthUser != authUser)
    {
        mAuthUser = authUser;
        emit authUserChanged();
    }
}

void QRestClient::setAuthPass(const QString& authPass)
{
    if (mAuthPass != authPass)
    {
        mAuthPass = authPass;
        emit authPassChanged();
    }
}

QNetworkRequest QRestClient::buildRequest(const QString& path) const
{
    QNetworkRequest request(mApiAddress.toString() + "/" + path);
    if (mAuthUser != "")
    {
        QString credentials = mAuthUser + ":" + mAuthPass;
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
    }
    return request;
}

void QRestClient::callGet(QRestCaller* caller, const QString& path)
{
    emit caller->beginUpdate();
    QNetworkRequest request = buildRequest(path);
    caller->setReply(get(request));
}
