
#include "sdk/controls/setup.h"
#include "sdk/controls/qcalcparaminteger.h"

QCalcParamInteger::QCalcParamInteger(QCalcable* parent, const char* parentSignal)
    : QCalcObject(parent)
    , mValue(0)
{
    parent->addParam(this);
    connect(this, SIGNAL(changed()), parent, parentSignal);
}

int QCalcParamInteger::value() const
{
    return mValue;
}

void QCalcParamInteger::setValue(int value)
{
    if (mValue != value)
    {
        mValue = value;
        emit changed();
    }
}
