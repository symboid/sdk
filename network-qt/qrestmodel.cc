
#include "sdk/network-qt/setup.h"
#include "sdk/network-qt/qrestmodel.h"

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
