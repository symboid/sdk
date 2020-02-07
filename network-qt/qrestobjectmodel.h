
#ifndef __SYMBOID_SDK_NETWORK_QT_QRESTOBJECTMODEL_H__
#define __SYMBOID_SDK_NETWORK_QT_QRESTOBJECTMODEL_H__

#include "sdk/network-qt/defs.h"
#include "sdk/network-qt/qrestmodel.h"
#include <QJsonObject>

class SDK_NETWORK_QT_API QRestObjectJSON : public QRestCaller
{
    Q_OBJECT

public:
    QRestObjectJSON(QObject* parent = Q_NULLPTR);

private:
    void fetchResult(QNetworkReply* reply) override;

private:
    QJsonObject mResultObject;
    QVector<QJsonObject::const_iterator> mFields;

public:
    int fieldCount() const;
    QVariant value(int fieldIndex) const;
    QString field(int fieldIndex) const;
    QVariant value(const QString& fieldName) const;

public:
    QJsonObject resultObject() const;
};

class SDK_NETWORK_QT_API QRestObjectModel : public QRestModel
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
    QRestObjectJSON mRestObject;

public:
    Q_PROPERTY(QJsonObject restObject READ restObject NOTIFY restObjectChanged)
private:
    QJsonObject restObject() const;
signals:
    void restObjectChanged();
};

#endif // __SYMBOID_SDK_NETWORK_QT_QRESTOBJECTMODEL_H__
