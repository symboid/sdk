
import QtQuick.Controls 2.5

SpinBox {

    property bool circular: false
    signal incrementedCircular()
    signal decrementedCircular()

    function increment()
    {
        if (value === to && circular)
        {
            value = from
            incrementedCircular()
        }
        else
        {
            increase()
        }
    }

    function decrement()
    {
        if (value === from && circular)
        {
            value = to
            decrementedCircular()
        }
        else
        {
            decrease()
        }
    }
}
