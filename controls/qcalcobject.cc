
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcobject.h"
#include "sdk/controls/qcalctask.h"

QCalcObject::QCalcObject(QObject *parent)
    : QObject(parent)
{
}

QCalcable::QCalcable(QObject* parent)
    : QCalcObject(parent)
    , mCalcTask(nullptr)
{
}

void QCalcable::setCalcTask(QCalcTask* calcTask)
{
    if (mCalcTask)
    {
        for (QCalcObject* param : mParams)
        {
            disconnect(param, SIGNAL(changed()), mCalcTask, SLOT(invoke()));
        }
    }
    mCalcTask = calcTask;
    if (mCalcTask)
    {
        for (QCalcObject* param : mParams)
        {
            connect(param, SIGNAL(changed()), mCalcTask, SLOT(invoke()));
        }
    }
    emit calcTaskChanged();
}

QCalcTask* QCalcable::calcTask() const
{
    return mCalcTask;
}

void QCalcable::addParam(QCalcObject* param)
{
    if (param)
    {
        if (mCalcTask)
        {
            connect(param, SIGNAL(changed()), mCalcTask, SLOT(invoke()));
        }
        mParams.push_back(param);
    }
}

void QCalcable::deleteParam(QCalcObject* param)
{
    if (param)
    {
        QList<QCalcObject*>::iterator d = mParams.begin();
        while (d != mParams.end() && *d == param)
        {
            ++d;
        }
        if (d != mParams.end())
        {
            if (mCalcTask)
            {
                disconnect(param, SIGNAL(changed()), mCalcTask, SLOT(invoke()));
            }
            mParams.erase(d);
        }
    }
}
