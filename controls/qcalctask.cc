
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalctask.h"
#include "sdk/controls/qcalcthread.h"

QCalcTask::QCalcTask(QObject* parent)
    : QObject(parent)
    , mExecThread(new QCalcThread(this))
    , mCalcable(nullptr)
    , mProgressPos(00L)
    , mProgressTotal(00L)
    , mIsValid(false)
    , mRunning(false)
    , mAutorun(false)
{
}

QCalcTask::~QCalcTask()
{
    mExecThread->deleteLater();
}

void QCalcTask::invoke()
{
    if (mAutorun)
    {
        start();
    }
    else
    {
        setValid(false);
    }
}

void QCalcTask::start()
{
    setValid(false);
    if (mExecThread->isRunning())
    {
        setRestarted();
    }
    else if (mCalcable)
    {
        mExecThread->start();
    }
}

void QCalcTask::exec()
{
    setRunning(true);
    emit started();
    setProgressPos(0LL);
    setProgressTotal(0LL);

    mCalcable->calc();

    setProgressPos(0LL);
    setProgressTotal(0LL);
    if (restarted())
    {
    }
    else if (isAborted())
    {
        setValid(false);
        emit aborted();
    }
    else
    {
        setValid(true);
        emit finished();
    }
    setRunning(false);
}

QCalcable* QCalcTask::calcable() const
{
    return mCalcable;
}

void QCalcTask::setCalcable(QCalcable* calcable)
{
    if (mCalcable != calcable)
    {
        mCalcable = calcable;
        if (mCalcable)
        {
            mCalcable->setCalcTask(this);
        }
        emit calcableChanged();
    }
}

void QCalcTask::run()
{
    QMutexLocker calcLocker(&mExecMutex);
    exec();
    while (restarting())
    {
        exec();
    }
    emit mCalcable->changed();
}

void QCalcTask::abort()
{
    mExecThread->requestInterruption();
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

bool QCalcTask::autorun() const
{
    return mAutorun;
}

void QCalcTask::setAutorun(bool autorun)
{
    if (mAutorun != autorun)
    {
        mAutorun = autorun;
        emit autorunChanged();
        if (mAutorun && !mIsValid)
        {
            start();
        }
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

bool QCalcTask::valid() const
{
    return mIsValid;
}

void QCalcTask::setValid(bool isValid)
{
    if (mIsValid != isValid)
    {
        mIsValid = isValid;
        emit validChanged();
    }
}

bool QCalcTask::isAborted() const
{
    return mExecThread->isInterruptionRequested();
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
