
#ifndef __SYMBOID_SDK_CONTROLS_QCALCTASK_H__
#define __SYMBOID_SDK_CONTROLS_QCALCTASK_H__

#include "sdk/controls/defs.h"
#include <QObject>
#include <QMutex>

class SDK_CONTROLS_API QCalcTask : public QObject
{
    Q_OBJECT

public:
    QCalcTask(QObject* parent);

public:
    virtual void calc() = 0;
    void run();

public:
    void setExecutionThread(QThread* executionthread);
    QThread* executionThread() const;
private:
    QThread* mExecutionThread;

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
private:
    bool mRunning;
public:
    bool running() const;
    void setRunning(bool running);
signals:
    void runningChanged();

public:
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
    qreal progress() const;
protected:
    void setProgressPos(qint64 progressPos);
    void setProgressTotal(qint64 progressTotal);
private:
    qint64 mProgressPos;
    qint64 mProgressTotal;
signals:
    void progressChanged();

public:
    bool isAborted() const;
signals:
    void finished();
    void aborted();

public:
    bool restarting();
    bool restarted();
    void setRestarted();
    QMutex mRestartMutex;
    int mRestartCount;
};

#endif // __SYMBOID_SDK_CONTROLS_QCALCTASK_H__
