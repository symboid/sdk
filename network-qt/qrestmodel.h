
#ifndef __SYMBOID_SDK_NETWORK_QT_QRESTMODEL_H__
#define __SYMBOID_SDK_NETWORK_QT_QRESTMODEL_H__

#include "sdk/network-qt/defs.h"
#include "sdk/network-qt/qrestclient.h"
#include <QAbstractListModel>

class SDK_NETWORK_QT_API QRestModel : public QAbstractListModel
{
    Q_OBJECT

protected:
    QRestModel(QObject* parent = Q_NULLPTR);
private:
    virtual QRestCaller* restCaller() = 0;

public:
    Q_PROPERTY(QRestClient* restClient MEMBER mRestClient WRITE setRestClient NOTIFY restClientChanged)
    void setRestClient(QRestClient* restClient);
protected:
    QRestClient* mRestClient;
signals:
    void restClientChanged();

public:
    Q_PROPERTY(QString operation MEMBER mOperation WRITE setOperation NOTIFY operationChanged)
protected:
    void setOperation(const QString& operation);
    QString mOperation;
signals:
    void operationChanged();

public slots:
    Q_INVOKABLE void runOperation();

signals:
    void networkError(QNetworkReply::NetworkError networkError);
};

#endif // __SYMBOID_SDK_NETWORK_QT_QRESTMODEL_H__
