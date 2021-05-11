
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalctask.h"
#include <QThread>

QCalcTask::QCalcTask(QObject* parent)
    : QObject(parent)
    , mExecutionThread(nullptr)
    , mRunning(false)
    , mProgressPos(00L)
    , mProgressTotal(00L)
{
}

void QCalcTask::run()
{
    setRunning(true);
    setProgressPos(0LL);
    setProgressTotal(0LL);

    calc();

    setProgressPos(0LL);
    setProgressTotal(0LL);
    if (!restarted())
    {
        emit isAborted() ? aborted() : finished();
    }
    setRunning(false);
}

void QCalcTask::setExecutionThread(QThread* executionThread)
{
    mExecutionThread = executionThread;
}

QThread* QCalcTask::executionThread() const
{
    return mExecutionThread;
}

bool QCalcTask::running() const
{
    return mRunning;
}

void QCalcTask::setRunning(bool running)
{
    if (mRunning != running)
    {
        mRunning = running;
        emit runningChanged();
    }
}

qreal QCalcTask::progress() const
{
    return mProgressTotal != 0LL ? qreal(mProgressPos) / qreal(mProgressTotal) : 0LL;
}

void QCalcTask::setProgressPos(qint64 progressPos)
{
    if (mProgressPos != progressPos)
    {
        mProgressPos = progressPos;
        emit progressChanged();
    }
}

void QCalcTask::setProgressTotal(qint64 progressTotal)
{
    if (mProgressTotal != progressTotal)
    {
        mProgressTotal = progressTotal;
        emit progressChanged();
    }
}

bool QCalcTask::isAborted() const
{
    return mExecutionThread->isInterruptionRequested();
}

bool QCalcTask::restarting()
{
    QMutexLocker lock(&mRestartMutex);
    bool isRestarted = mRestartCount > 0;
    mRestartCount = 0;
    return isRestarted;
}

bool QCalcTask::restarted()
{
    QMutexLocker lock(&mRestartMutex);
    return mRestartCount > 0;
}

void QCalcTask::setRestarted()
{
    QMutexLocker lock(&mRestartMutex);
    mRestartCount++;
}
