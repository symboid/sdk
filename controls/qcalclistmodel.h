
#ifndef __SYMBOID_SDK_CONTROLS_QCALCLISTMODEL_H__
#define __SYMBOID_SDK_CONTROLS_QCALCLISTMODEL_H__

#include "sdk/controls/defs.h"
#include <QAbstractListModel>
#include "sdk/controls/qcalcobject.h"

class SDK_CONTROLS_API QCalcListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QCalcListModel(QObject* parent = Q_NULLPTR);

public:
    QCalcable* calcable() const;
    void setCalcable(QCalcable* calcable);
private:
    QCalcable* mCalcable;

private slots:
    void connectCalcSignals();
    void onRecalcStarted();
    void onRecalcFinished();
    void onRecalcAborted();
};

#endif // __SYMBOID_SDK_CONTROLS_QCALCLISTMODEL_H__
