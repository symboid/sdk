
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcthread.h"

QCalcThread::QCalcThread(QObject* parent, QCalcTask* calcTask)
    : QThread(parent)
    , mCalcTask(calcTask)
{
    mCalcTask->setExecutionThread(this);
}

void QCalcThread::run()
{
    QMutexLocker calcLocker(&mCalcMutex);
    mCalcTask->run();
    while (mCalcTask->restarting())
    {
        mCalcTask->run();
    }
}

void QCalcThread::startCalc()
{
    if (isRunning())
    {
        mCalcTask->setRestarted();
    }
    else
    {
        start();
    }
}
