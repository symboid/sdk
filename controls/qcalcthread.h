
#ifndef __SYMBOID_SDK_CONTROLS_QCALCTHREAD_H__
#define __SYMBOID_SDK_CONTROLS_QCALCTHREAD_H__

#include "sdk/controls/defs.h"
#include <QThread>

class QCalcTask;

class SDK_CONTROLS_API QCalcThread : public QThread
{
    Q_OBJECT
public:
    QCalcThread(QObject* parent, QCalcTask* calcTask);

private:
    void run() override;
public:
    void startCalc();

private:
    QCalcTask* mCalcTask;
    QMutex mCalcMutex;
};

#endif // __SYMBOID_SDK_CONTROLS_QCALCTHREAD_H__
