
import QtQuick 2.12

MultiNumberBox {

    property int hour: box(0).value
    property int minute: box(1).value
    property int second: box(2).value

    property CircularSpinBox dayLink: circularLink

    boxes: Row {
        NumberBox {
            id: hourBox
            from: 0
            to: 23
            displaySuffix: qsTr("h")
            value: (new Date).getHours()
            circularLink: dayLink
        }
        NumberBox {
            id: minuteBox
            from: 0
            to: 59
            digitCount: 2
            displaySuffix: qsTr("m")
            value: (new Date).getMinutes()
            circularLink: hourBox
        }
        NumberBox {
            id: secondBox
            from: 0
            to: 59
            digitCount: 2
            displaySuffix: qsTr("s")
            value: (new Date).getSeconds()
            circularLink: minuteBox
        }
    }
    function setCurrent()
    {
        var current = new Date
        box(0).value = current.getHours()
        box(1).value = current.getMinutes()
        box(2).value = current.getSeconds()
    }
    Component.onCompleted: {
        setCurrent()
    }
}
