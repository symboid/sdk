
#ifndef __SYMBOID_SDK_NETWORK_QT_QRESTCLIENT_H__
#define __SYMBOID_SDK_NETWORK_QT_QRESTCLIENT_H__

#include "sdk/network-qt/defs.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class SDK_NETWORK_QT_API QRestCaller : public QObject
{
    Q_OBJECT

public:
    QRestCaller(QObject* parent = Q_NULLPTR);

public:
    void setReply(QNetworkReply* reply);
private:
    QNetworkReply* mReply;

private slots:
    void onFinished();
private:
    virtual void fetchResult(QNetworkReply*) {}
signals:
    void beginUpdate();
    void beginUpdateResult();
    void endUpdateResult();
    void endUpdate();

private slots:
    void onError(QNetworkReply::NetworkError error);
private:
    QNetworkReply::NetworkError mStatus;
public:
    QNetworkReply::NetworkError status() const { return mStatus; }
};

class SDK_NETWORK_QT_API QRestClient : public QNetworkAccessManager
{
    Q_OBJECT

public:
    QRestClient(const QUrl& apiAddress, QObject* parent = Q_NULLPTR);
    virtual ~QRestClient() = default;

public:
    Q_PROPERTY(QUrl apiAddress MEMBER mApiAddress WRITE setApiAddress NOTIFY apiAddressChanged)
    void setApiAddress(const QUrl& apiAddress);
private:
    QUrl mApiAddress;
signals:
    void apiAddressChanged();

public:
    Q_PROPERTY(QString authUser MEMBER mAuthUser WRITE setAuthUser NOTIFY authUserChanged)
    Q_PROPERTY(QString authPass MEMBER mAuthPass WRITE setAuthPass NOTIFY authPassChanged)
    void setAuthUser(const QString& authUser);
    void setAuthPass(const QString& authPass);
private:
    QString mAuthUser;
    QString mAuthPass;
signals:
    void authUserChanged();
    void authPassChanged();

protected:
    QNetworkRequest buildRequest(const QString& path) const;

public:
    void callGet(QRestCaller* caller, const QString& path);
};

class SDK_NETWORK_QT_API QRestClientJSON : public QRestClient
{
    Q_OBJECT

public:
    QRestClientJSON(const QUrl& apiAddress, QObject* parent = Q_NULLPTR);
};

#endif // __SYMBOID_SDK_NETWORK_QT_QRESTCLIENT_H__
