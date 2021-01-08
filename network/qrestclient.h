
#ifndef __SYMBOID_SDK_NETWORK_QRESTCLIENT_H__
#define __SYMBOID_SDK_NETWORK_QRESTCLIENT_H__

#include "sdk/network/defs.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "sdk/arch/mainobject.h"

class SDK_NETWORK_API QRestCaller : public QObject
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
    void networkError(QNetworkReply::NetworkError);
    void apiError();

private slots:
    void onError(QNetworkReply::NetworkError error);
private:
    QNetworkReply::NetworkError mStatus;
public:
    QNetworkReply::NetworkError status() const { return mStatus; }

public:
    void setResultCompact(bool isResultCompact);
protected:
    bool mIsResultCompact;
};

class SDK_NETWORK_API QRestClient : public QNetworkAccessManager
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "RestClient";

public:
    QRestClient(QObject* parent = Q_NULLPTR);
    virtual ~QRestClient() = default;

public:
    Q_PROPERTY(bool secure MEMBER mIsSecure WRITE setSecure NOTIFY secureChanged)
    void setSecure(bool secure);
private:
    bool mIsSecure;
signals:
    void secureChanged();

public:
    Q_PROPERTY(QString apiAddress MEMBER mApiAddress WRITE setApiAddress NOTIFY apiAddressChanged)
    void setApiAddress(const QString& apiAddress);
private:
    QString mApiAddress;
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

Q_DECLARE_METATYPE(QRestClient*)

#endif // __SYMBOID_SDK_NETWORK_QRESTCLIENT_H__
