
#ifndef __SYMBOID_SDK_CONTROLS_QCALCPROPERTY_H__
#define __SYMBOID_SDK_CONTROLS_QCALCPROPERTY_H__

#include "sdk/controls/defs.h"
#include "sdk/controls/qcalcobject.h"

template <typename ParamType>
class QCalcPropertyWrapper : public QCalcObject
{
public:
    QCalcPropertyWrapper(QCalcable* parent, const char* parentSignal)
        : QCalcObject(parent)
        , mValue(0)
    {
        parent->addParam(this);
        connect(this, SIGNAL(changed()), parent, parentSignal);
    }

public:
    inline const ParamType& value() const { return mValue; }
    inline void setValue(const ParamType& value)
    {
        if (mValue != value)
        {
            mValue = value;
            emit changed();
        }
    }
    inline operator ParamType() const { return mValue; }

private:
    ParamType mValue;
};

#define Q_CALC_PROPERTY(Type, name) \
    public: \
        Q_PROPERTY(Type name READ name##Get WRITE name##Set NOTIFY name##Changed) \
        inline Type name##Get() const { return m_##name->value(); } \
        inline void name##Set(Type name##Value) { m_##name->setValue(name##Value); } \
    private: \
        QScopedPointer<QCalcPropertyWrapper<Type>> m_##name = \
                QScopedPointer<QCalcPropertyWrapper<Type>>(new QCalcPropertyWrapper<Type>(this, SIGNAL(name##Changed()))); \
    Q_SIGNALS: \
        void name##Changed();


#endif // __SYMBOID_SDK_CONTROLS_QCALCPROPERTY_H__
