
#include "sdk/network-qt/setup.h"
#include "sdk/network-qt/qresttablemodel.h"
#include <QJsonDocument>
#include <QJsonObject>

QRestObjectJSON::QRestObjectJSON(QObject* parent)
    : QRestCaller(parent)
{
}

void QRestObjectJSON::fetchResult(QNetworkReply* reply)
{
    if (reply)
    {
        mResultObject = QJsonDocument::fromJson(reply->readAll()).object();
        QJsonObject::const_iterator it = mResultObject.constBegin();
        while (it != mResultObject.constEnd())
        {
            mFields.push_back(it);
            ++it;
        }
    }
}

int QRestObjectJSON::fieldCount() const
{
    return mResultObject.count();
}

QVariant QRestObjectJSON::value(int fieldIndex) const
{
    return 0 <= fieldIndex && fieldIndex < mFields.size() ? mFields.at(fieldIndex).value() : QVariant();
}

QString QRestObjectJSON::field(int fieldIndex) const
{
    return 0 <= fieldIndex && fieldIndex < mFields.size() ? mFields.at(fieldIndex).key() : QString();
}

QVariant QRestObjectJSON::value(const QString& fieldName) const
{
    return mResultObject[fieldName].toVariant();
}

QRestTableJSON::QRestTableJSON(QObject* parent)
    : QRestCaller(parent)
    , mRowCount(0)
{
}

void QRestTableJSON::fetchResult(QNetworkReply* reply)
{
    if (reply)
    {
        QJsonObject rootObject = QJsonDocument::fromJson(reply->readAll()).object();
        mResultArray = rootObject.begin()->toArray();
        mRowCount = mResultArray.count();
    }
}

int QRestTableJSON::rowCount() const
{
    return mRowCount;
}

QVariant QRestTableJSON::value(int rowIndex, const QString& columnName) const
{
    return mResultArray[rowIndex].toObject().value(columnName).toVariant();
}

QRestModel::QRestModel(QObject* parent)
    : QAbstractListModel(parent)
    , mRestClient(Q_NULLPTR)
{
}

void QRestModel::setRestClient(QRestClient* restClient)
{
    if (mRestClient != restClient)
    {
        mRestClient = restClient;
        emit restClientChanged();
    }
}

void QRestModel::setOperation(const QString& operation)
{
    if (mOperation != operation)
    {
        mOperation = operation;
        emit operationChanged();
    }
}

void QRestModel::runOperation()
{
    if (mRestClient != Q_NULLPTR && mOperation != "")
    {
        mRestClient->callGet(restCaller(), mOperation);
    }
}

QRestObjectModel::QRestObjectModel(QObject* parent)
    : QRestModel(parent)
{
    connect(&mRestObject, SIGNAL(beginUpdate()), this, SIGNAL(modelAboutToBeReset()));
    connect(&mRestObject, SIGNAL(endUpdate()), this, SIGNAL(modelReset()));
    connect(&mRestObject, SIGNAL(networkError(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
}

int QRestObjectModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mRestObject.fieldCount();
}

QVariant QRestObjectModel::data(const QModelIndex& index, int role) const
{
    return role == Qt::UserRole ? mRestObject.field(index.row()) : mRestObject.value(index.row());
}

QHash<int, QByteArray> QRestObjectModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Qt::UserRole] = "field";
    return roles;
}

QRestTableModel::QRestTableModel(QObject* parent)
    : QRestModel(parent)
{
    connect(&mRestTable, SIGNAL(beginUpdate()), this, SIGNAL(modelAboutToBeReset()));
    connect(&mRestTable, SIGNAL(endUpdate()), this, SIGNAL(modelReset()));
    connect(&mRestTable, SIGNAL(networkError(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
}

int QRestTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mRestTable.rowCount();
}

QVariant QRestTableModel::data(const QModelIndex& index, int role) const
{
    QString columnName = mColumnNames.at(role - Qt::UserRole);
    return mRestTable.value(index.row(), columnName);
}

QHash<int, QByteArray> QRestTableModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    int roleIndex = Qt::UserRole;
    for (QString colName : mColumnNames)
    {
        roles[roleIndex++] = QByteArray(colName.toUtf8().data());
    }
    return roles;
}

void QRestTableModel::setColumnNames(const QStringList &columnNames)
{
    if (mColumnNames != columnNames)
    {
        mColumnNames = columnNames;
        emit columnNamesChanged();
    }
}
