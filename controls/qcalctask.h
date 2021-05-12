
#ifndef __SYMBOID_SDK_CONTROLS_QCALCTASK_H__
#define __SYMBOID_SDK_CONTROLS_QCALCTASK_H__

#include "sdk/controls/defs.h"
#include <QObject>
#include <QMutex>

class QCalcThread;

class SDK_CONTROLS_API QCalcTask : public QObject
{
    Q_OBJECT

public:
    QCalcTask(QObject* parent);
    ~QCalcTask();

public:
    virtual void calc() = 0;
    void invoke();
    void start();
    void run();
    void abort();

private:
    QCalcThread* mExecutionThread;

public:
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
public:
    qreal progress() const;
    void setProgressPos(qint64 progressPos);
    void setProgressTotal(qint64 progressTotal);
private:
    qint64 mProgressPos;
    qint64 mProgressTotal;
signals:
    void progressChanged();

public:
    Q_PROPERTY(bool valid READ valid WRITE setValid NOTIFY validChanged)
public:
    bool valid() const;
private:
    bool mIsValid;
    void setValid(bool isValid);
signals:
    void validChanged();

public:
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
private:
    bool mRunning;
public:
    bool running() const;
    void setRunning(bool running);
signals:
    void runningChanged();

public:
    Q_PROPERTY(bool autorun READ autorun WRITE setAutorun NOTIFY autorunChanged)
private:
    bool mAutorun;
public:
    bool autorun() const;
    void setAutorun(bool running);
signals:
    void autorunChanged();

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
