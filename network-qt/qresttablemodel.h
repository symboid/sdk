
#ifndef __SYMBOID_SDK_NETWORK_QT_QRESTTABLEMODEL_H__
#define __SYMBOID_SDK_NETWORK_QT_QRESTTABLEMODEL_H__

#include "sdk/network-qt/defs.h"
#include "sdk/network-qt/qrestclient.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QAbstractListModel>

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
};

class SDK_NETWORK_QT_API QRestTableJSON : public QRestCaller
{
    Q_OBJECT

public:
    QRestTableJSON(QObject* parent = Q_NULLPTR);

private:
    void fetchResult(QNetworkReply* reply) override;

private:
    QJsonArray mResultArray;
    int mRowCount;

public:
    int rowCount() const;
    QVariant value(int rowIndex, const QString& columnName) const;
};

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
};

class SDK_NETWORK_QT_API QRestTableModel : public QRestModel
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "RestTableModel";

public:
    QRestTableModel(QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QRestCaller* restCaller() override { return &mRestTable; }
    QRestTableJSON mRestTable;

public:
    Q_PROPERTY(QStringList columnNames MEMBER mColumnNames WRITE setColumnNames NOTIFY columnNamesChanged)
    void setColumnNames(const QStringList& columnNames);
private:
    QStringList mColumnNames;
signals:
    void columnNamesChanged();
};

Q_DECLARE_METATYPE(QRestClient*)

#endif // __SYMBOID_SDK_NETWORK_QT_QRESTTABLEMODEL_H__
