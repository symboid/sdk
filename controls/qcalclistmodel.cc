
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalclistmodel.h"
#include "sdk/controls/qcalctask.h"

QCalcListModel::QCalcListModel(QObject* parent)
    : QAbstractListModel(parent)
    , mCalcable(nullptr)
{
}

QCalcable* QCalcListModel::calcable() const
{
    return mCalcable;
}

void QCalcListModel::setCalcable(QCalcable* calcable)
{
    if (mCalcable != calcable)
    {
        if (mCalcable)
        {
            disconnect(mCalcable, SIGNAL(calcTaskChanged()), this, SLOT(connectCalcSignals()));
        }
        if ((mCalcable = calcable))
        {
            connect(mCalcable, SIGNAL(calcTaskChanged()), this, SLOT(connectCalcSignals()));
            connectCalcSignals();
        }
    }
}

void QCalcListModel::connectCalcSignals()
{
    if (QCalcTask* calcTask = mCalcable->calcTask())
    {
        connect(calcTask, SIGNAL(started()), this, SLOT(onRecalcStarted()));
        connect(calcTask, SIGNAL(finished()), this, SLOT(onRecalcFinished()));
        connect(calcTask, SIGNAL(aborted()), this, SLOT(onRecalcAborted()));
    }
}

void QCalcListModel::onRecalcStarted()
{
    beginResetModel();
}

void QCalcListModel::onRecalcFinished()
{
    endResetModel();
}

void QCalcListModel::onRecalcAborted()
{
    endResetModel();
}
