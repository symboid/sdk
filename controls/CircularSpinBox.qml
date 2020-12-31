
import QtQuick.Controls 2.5
import QtQuick 2.12

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

    onActiveFocusChanged: {
        if (activeFocus)
        {
            // context property ApplicationWindow.activeFocusItem refers
            // onto the TextField inside a SpinBox when focused
            if (activeFocusItem instanceof TextInput)
            {
                activeFocusItem.selectAll()
            }
        }
    }
    activeFocusOnTab: true
}
