
#ifndef __SYMBOID_SDK_CONTROLS_QCALCOBJECT_H__
#define __SYMBOID_SDK_CONTROLS_QCALCOBJECT_H__

#include "sdk/controls/defs.h"
#include <QObject>

class SDK_CONTROLS_API QCalcObject : public QObject
{
    Q_OBJECT

public:
    QCalcObject(QObject *parent);

signals:
    void changed();
};

class QCalcTask;

class SDK_CONTROLS_API QCalcable : public QCalcObject
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "Calcable";
public:
    QCalcable(QObject* parent = Q_NULLPTR);

public:
    virtual void calc() = 0;

public:
    void setCalcTask(QCalcTask* calcTask);
    QCalcTask* calcTask() const;
protected:
    QCalcTask* mCalcTask;
signals:
    void calcTaskChanged();

public:
    void addParam(QCalcObject* param);
    void deleteParam(QCalcObject* param);
private:
    QList<QCalcObject*> mParams;
};

Q_DECLARE_METATYPE(QCalcable*)

#endif // __SYMBOID_SDK_CONTROLS_QCALCOBJECT_H__
