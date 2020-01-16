
import QtQuick.Controls 2.5

SpinBox {

    property bool circular: false
    signal incrementedCircular()
    signal decrementedCircular()

    function increment()
    {
        if (value === to && circular)
        {
            while (value > from) decrease()
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
            while (value < to) increase()
            decrementedCircular()
        }
        else
        {
            decrease()
        }
    }
}
