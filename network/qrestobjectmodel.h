
#ifndef __SYMBOID_SDK_NETWORK_QRESTOBJECTMODEL_H__
#define __SYMBOID_SDK_NETWORK_QRESTOBJECTMODEL_H__

#include "sdk/network/defs.h"
#include "sdk/network/qrestmodel.h"
#include <QJsonObject>

class SDK_NETWORK_API QRestObject : public QRestCaller
{
    Q_OBJECT

public:
    QRestObject(QObject* parent = Q_NULLPTR);

private:
    void fetchResult(QNetworkReply* reply) override;

private:
    bool mIsValid;
    QJsonObject mResultObject;
    QVector<QJsonObject::const_iterator> mFields;

public:
    bool isValid() const;
    int fieldCount() const;
    QVariant value(int fieldIndex) const;
    QString field(int fieldIndex) const;
    QVariant value(const QString& fieldName) const;

public:
    QJsonObject resultObject() const;

signals:
    void isValidChanged();
};

class SDK_NETWORK_API QRestObjectModel : public QRestModel
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "RestObjectModel";

public:
    QRestObjectModel(QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QRestCaller* restCaller() override { return &mRestObject; }
    QRestObject mRestObject;

public:
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
    Q_PROPERTY(QJsonObject restObject READ restObject NOTIFY restObjectChanged)
private:
    bool isValid() const;
    QJsonObject restObject() const;
signals:
    void isValidChanged();
    void restObjectChanged();
};

#endif // __SYMBOID_SDK_NETWORK_QRESTOBJECTMODEL_H__
