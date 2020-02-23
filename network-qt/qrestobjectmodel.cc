
#include "sdk/network-qt/setup.h"
#include "sdk/network-qt/qrestobjectmodel.h"
#include <QJsonDocument>

QRestObjectJSON::QRestObjectJSON(QObject* parent)
    : QRestCaller(parent)
{
}

void QRestObjectJSON::fetchResult(QNetworkReply* reply)
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
            mResultObject = replyDocument.object();
            QJsonObject::const_iterator it = mResultObject.constBegin();
            while (it != mResultObject.constEnd())
            {
                mFields.push_back(it);
                ++it;
            }
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

QJsonObject QRestObjectJSON::resultObject() const
{
    return mResultObject;
}

QRestObjectModel::QRestObjectModel(QObject* parent)
    : QRestModel(parent)
{
    connect(&mRestObject, SIGNAL(beginUpdate()), this, SIGNAL(modelAboutToBeReset()));
    connect(&mRestObject, SIGNAL(endUpdate()), this, SIGNAL(modelReset()));
    connect(&mRestObject, SIGNAL(endUpdate()), this, SIGNAL(restObjectChanged()));
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

QJsonObject QRestObjectModel::restObject() const
{
    return mRestObject.resultObject();
}
