
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcobject.h"
#include "sdk/controls/qcalctask.h"

QCalcObject::QCalcObject(QObject *parent)
    : QObject(parent)
    , mCalcable(nullptr)
{
}

QCalcable* QCalcObject::calcable() const
{
    return mCalcable;
}

void QCalcObject::setCalcable(QCalcable* calcable)
{
    if (mCalcable)
    {
        disconnect(this, SIGNAL(changed()), mCalcable, SIGNAL(changed()));
    }
    mCalcable = calcable;
    if (mCalcable)
    {
        connect(this, SIGNAL(changed()), mCalcable, SIGNAL(changed()));
    }
}

QCalcable::QCalcable(QObject* parent)
    : QCalcObject(parent)
    , mCalcTask(nullptr)
{
}

void QCalcable::setCalcTask(QCalcTask* calcTask)
{
    mCalcTask = calcTask;
    emit calcTaskChanged();
}

QCalcTask* QCalcable::calcTask() const
{
    return mCalcTask;
}

