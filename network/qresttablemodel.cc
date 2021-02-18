
#include "sdk/network/setup.h"
#include "sdk/network/qresttablemodel.h"
#include <QJsonDocument>
#include <QJsonObject>

QRestTableJSON::QRestTableJSON(QObject* parent)
    : QRestCaller(parent)
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
            if (replyDocument.isArray())
            {
                mResultArray = replyDocument.array();
            }
            else if (mArrayPath != "")
            {
                QJsonValue field(replyDocument.object());
                for (QString fieldName : mArrayPath.split('.'))
                {
                    field = field.toObject()[fieldName];
                }
                mResultArray = field.toArray();
            }
            else
            {
                QJsonObject rootObject(replyDocument.object());
                mResultArray = rootObject.begin()->toArray();
            }
        }
    }
}

const QJsonArray& QRestTableJSON::resultArray() const
{
    return mResultArray;
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
    Q_UNUSED(parent)
    return mRestTable.resultArray().size() + (mExtraValue != "" ? 1 : 0);
}

QVariant QRestTableModel::data(const QModelIndex& index, int role) const
{
    int rowIndex = index.row();
    if (mExtraValue != "")
    {
        rowIndex--;
    }
    if (rowIndex == -1)
    {
        return mExtraValue;
    }
    else
    {
        QString columnName = mColumnNames.at(role - Qt::UserRole);
        return mRestTable.resultArray()[rowIndex].toObject().value(columnName).toVariant();
    }
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

const QRestTableJSON& QRestTableModel::restTable() const
{
    return mRestTable;
}

const QStringList& QRestTableModel::columnNames() const
{
    return mColumnNames;
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
    return mRestTable.resultArray().size();
}

QJsonObject QRestTableModel::object(int objectIndex) const
{
    return mRestTable.resultArray()[objectIndex].toObject();
}

QJsonObject QRestTableModel::firstObject() const
{
    const QJsonArray& resultArray(mRestTable.resultArray());
    return resultArray.size() > 0 ? resultArray[0].toObject() : QJsonObject();
}

void QRestTableModel::setExtraValue(const QString& extraValue)
{
    if (mExtraValue != extraValue)
    {
        mExtraValue = extraValue;
        emit extraValueChanged();
    }
}

QString QRestTableModel::arrayPath() const
{
    return mRestTable.mArrayPath;
}

void QRestTableModel::setArrayPath(const QString& arrayPath)
{
    if (mRestTable.mArrayPath != arrayPath)
    {
        mRestTable.mArrayPath = arrayPath;
        emit arrayPathChanged();
    }
}
