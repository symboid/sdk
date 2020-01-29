
import QtQuick.Controls 2.5

SpinBox {

    property bool circular: false
    signal incrementedCircular()
    signal decrementedCircular()

    function increment()
    {
        if (value === to && circular)
        {
            incrementedCircular()
            while (value > from) decrease()
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
            decrementedCircular()
            while (value < to) increase()
        }
        else
        {
            decrease()
        }
    }
}
