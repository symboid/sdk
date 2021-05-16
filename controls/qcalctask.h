
#ifndef __SYMBOID_SDK_CONTROLS_QCALCTASK_H__
#define __SYMBOID_SDK_CONTROLS_QCALCTASK_H__

#include "sdk/controls/defs.h"
#include "sdk/controls/qcalcobject.h"
#include <QObject>
#include <QMutex>

class SDK_CONTROLS_API QCalcTask : public QObject
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "CalcTask";

public:
    QCalcTask(QObject* parent = Q_NULLPTR);
    ~QCalcTask();

private:
    void exec();
public:
    Q_INVOKABLE void start();
    Q_INVOKABLE void abort();
public slots:
    void run();
    void invoke();

private:
    QThread* mExecThread;
    QMutex mExecMutex;

public:
    Q_PROPERTY(QCalcable* calcable READ calcable WRITE setCalcable NOTIFY calcableChanged)
    QCalcable* calcable() const;
    void setCalcable(QCalcable* calcable);
private:
    QCalcable* mCalcable;
signals:
    void calcableChanged();

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
    void started();
    void finished();
    void aborted();

public:
    bool restarting();
    bool restarted();
    void setRestarted();
    QMutex mRestartMutex;
    int mRestartCount;
};

Q_DECLARE_METATYPE(QCalcTask*)

#endif // __SYMBOID_SDK_CONTROLS_QCALCTASK_H__
