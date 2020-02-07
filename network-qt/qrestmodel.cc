
#include "sdk/network-qt/setup.h"
#include "sdk/network-qt/qrestmodel.h"

QRestModel::QRestModel(QObject* parent)
    : QAbstractListModel(parent)
    , mRestClient(Q_NULLPTR)
    , mInteractive(false)
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

void QRestModel::setInteractive(bool interactive)
{
    if (mInteractive != interactive)
    {
        mInteractive = interactive;
        if (mInteractive)
        {
            connect(this, SIGNAL(operationChanged()), this, SLOT(runOperation()));
            runOperation();
        }
        else
        {
            disconnect(this, SIGNAL(operationChanged()), this, SLOT(runOperation()));
        }
        emit interactiveChanged();
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
