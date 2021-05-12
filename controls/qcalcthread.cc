
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcthread.h"
#include "sdk/controls/qcalctask.h"

QCalcThread::QCalcThread(QObject* parent, QCalcTask* calcTask)
    : QThread(parent)
    , mCalcTask(calcTask)
{
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
