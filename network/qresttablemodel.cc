
#include "sdk/network/setup.h"
#include "sdk/network/qresttablemodel.h"
#include <QJsonDocument>
#include <QJsonObject>

QRestTableJSON::QRestTableJSON(QObject* parent)
    : QRestCaller(parent)
    , mRowCount(0)
{
}

void QRestTableJSON::fetchResult(QNetworkReply* reply)
{
    if (reply)
    {
        QJsonDocument replyDocument = QJsonDocument::fromJson(reply->readAll());
        if (replyDocument.isNull())
        {
            // empty json reply --> wrong parameters at request
            emit apiError();
        }
        else
        {
            QJsonObject rootObject(replyDocument.object());
            mResultArray = rootObject.begin()->toArray();
            mRowCount = mResultArray.count();
        }
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

QJsonObject QRestTableJSON::rowObject(int rowIndex) const
{
    return mResultArray[rowIndex].toObject();
}

QRestTableModel::QRestTableModel(QObject* parent)
    : QRestModel(parent)
{
    connect(&mRestTable, SIGNAL(beginUpdate()), this, SIGNAL(modelAboutToBeReset()));
    connect(&mRestTable, SIGNAL(endUpdate()), this, SIGNAL(modelReset()));
    connect(&mRestTable, SIGNAL(endUpdate()), this, SIGNAL(firstObjectChanged()));
    connect(&mRestTable, SIGNAL(endUpdateResult()), this, SIGNAL(objectCountChanged()));
    connect(&mRestTable, SIGNAL(endUpdateResult()), this, SIGNAL(successfullyFinished()));
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

int QRestTableModel::objectCount() const
{
    return mRestTable.rowCount();
}

QJsonObject QRestTableModel::object(int objectIndex) const
{
    return mRestTable.rowObject(objectIndex);
}

QJsonObject QRestTableModel::firstObject() const
{
    return mRestTable.rowCount() > 0 ? mRestTable.rowObject(0) : QJsonObject();
}
