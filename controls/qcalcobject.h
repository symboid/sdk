
#ifndef __SYMBOID_SDK_CONTROLS_QCALCOBJECT_H__
#define __SYMBOID_SDK_CONTROLS_QCALCOBJECT_H__

#include "sdk/controls/defs.h"
#include <QObject>

class QCalcable;

class QCalcObject : public QObject
{
    Q_OBJECT

public:
    explicit QCalcObject(QObject *parent = nullptr);

signals:
    void changed();

public:
    QCalcable* calcable() const;
    void setCalcable(QCalcable* calcable);
private:
    QCalcable* mCalcable;
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
};

Q_DECLARE_METATYPE(QCalcable*)

#endif // __SYMBOID_SDK_CONTROLS_QCALCOBJECT_H__
