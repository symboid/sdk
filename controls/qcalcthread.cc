
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcthread.h"
#include "sdk/controls/qcalctask.h"

QCalcThread::QCalcThread(QCalcTask* calcTask)
    : QThread(calcTask)
    , mCalcTask(calcTask)
{
}

void QCalcThread::run()
{
    mCalcTask->run();
}
