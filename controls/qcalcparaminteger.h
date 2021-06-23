
#ifndef __SYMBOID_SDK_CONTROLS_QCALCPARAMINTEGER_H__
#define __SYMBOID_SDK_CONTROLS_QCALCPARAMINTEGER_H__

#include "sdk/controls/defs.h"
#include "sdk/controls/qcalcobject.h"

class SDK_CONTROLS_API QCalcParamInteger : public QCalcObject
{
    Q_OBJECT
public:
    QCalcParamInteger(QCalcable* parent, const char* parentSignal);

public:
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY changed)
    int value() const;
    void setValue(int value);
private:
    int mValue;
};

#define Q_CALC_PARAM_INTEGER(name) \
public: \
    Q_PROPERTY(int name READ name##Get WRITE name##Set NOTIFY name##Changed) \
    int name##Get() const { return m_##name->value(); } \
    void name##Set(int name##Value) { m_##name->setValue(name##Value); } \
private: \
    QScopedPointer<QCalcParamInteger> m_##name = \
            QScopedPointer<QCalcParamInteger>(new QCalcParamInteger(this, SIGNAL(name##Changed()))); \
Q_SIGNALS: \
    void name##Changed();

#endif // __SYMBOID_SDK_CONTROLS_QCALCPARAMINTEGER_H__
