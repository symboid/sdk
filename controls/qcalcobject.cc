
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcobject.h"
#include "sdk/controls/qcalctask.h"

QCalcObject::QCalcObject(QObject *parent)
    : QObject(parent)
{
}

QCalcParam::QCalcParam(QObject *parent)
    : QCalcObject(parent)
    , mCalcable(nullptr)
{
}

QCalcable* QCalcParam::calcable() const
{
    return mCalcable;
}

void QCalcParam::setCalcable(QCalcable* calcable)
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
    if (mCalcTask)
    {
        disconnect(this, SIGNAL(changed()), mCalcTask, SLOT(invoke()));
    }
    mCalcTask = calcTask;
    if (mCalcTask)
    {
        connect(this, SIGNAL(changed()), mCalcTask, SLOT(invoke()));
    }
    emit calcTaskChanged();
}

QCalcTask* QCalcable::calcTask() const
{
    return mCalcTask;
}
