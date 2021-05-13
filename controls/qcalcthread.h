
#ifndef __SYMBOID_SDK_CONTROLS_QCALCTHREAD_H__
#define __SYMBOID_SDK_CONTROLS_QCALCTHREAD_H__

#include "sdk/controls/defs.h"
#include <QThread>
#include <QMutex>

class QCalcTask;

class SDK_CONTROLS_API QCalcThread : public QThread
{
    Q_OBJECT
public:
    QCalcThread(QCalcTask* calcTask);

private:
    void run() override;

private:
    QCalcTask* mCalcTask;
};

#endif // __SYMBOID_SDK_CONTROLS_QCALCTHREAD_H__
