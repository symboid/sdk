
#include "sdk/network/setup.h"
#include "sdk/network/qrestobjectmodel.h"
#include <QJsonDocument>

QRestObject::QRestObject(QObject* parent)
    : QRestCaller(parent)
    , mIsValid(false)
{
}

void QRestObject::fetchResult(QNetworkReply* reply)
{
    mIsValid = false;
    emit isValidChanged();
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
            mIsValid = true;
            emit isValidChanged();
        }
    }
}

bool QRestObject::isValid() const
{
    return mIsValid;
}

int QRestObject::fieldCount() const
{
    return mResultObject.count();
}

QVariant QRestObject::value(int fieldIndex) const
{
    return 0 <= fieldIndex && fieldIndex < mFields.size() ? mFields.at(fieldIndex).value().toVariant() : QVariant();
}

QString QRestObject::field(int fieldIndex) const
{
    return 0 <= fieldIndex && fieldIndex < mFields.size() ? mFields.at(fieldIndex).key() : QString();
}

QVariant QRestObject::value(const QString& fieldName) const
{
    return mResultObject[fieldName].toVariant();
}

QJsonObject QRestObject::resultObject() const
{
    return mResultObject;
}

QRestObjectModel::QRestObjectModel(QObject* parent)
    : QRestModel(parent)
{
    connect(&mRestObject, SIGNAL(beginUpdate()), this, SIGNAL(modelAboutToBeReset()));
    connect(&mRestObject, SIGNAL(endUpdate()), this, SIGNAL(modelReset()));
    connect(&mRestObject, SIGNAL(endUpdateResult()), this, SIGNAL(restObjectChanged()));
    connect(&mRestObject, SIGNAL(endUpdateResult()), this, SIGNAL(successfullyFinished()));
    connect(&mRestObject, SIGNAL(networkError(QNetworkReply::NetworkError)), this, SIGNAL(networkError(QNetworkReply::NetworkError)));
    connect(&mRestObject, SIGNAL(isValidChanged()), this, SIGNAL(isValidChanged()));
}

int QRestObjectModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
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

bool QRestObjectModel::isValid() const
{
    return mRestObject.isValid();
}

QJsonObject QRestObjectModel::restObject() const
{
    return mRestObject.resultObject();
}
