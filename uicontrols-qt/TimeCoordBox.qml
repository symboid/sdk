
import QtQuick 2.12

MultiNumberBox {

    property int hour: box(0).value
    onHourChanged: {
        box(0).value = hour
        hour = Qt.binding(function(){return box(0).value})
    }
    property int minute: box(2).value
    onMinuteChanged: {
        box(2).value = minute
        minute = Qt.binding(function(){return box(2).value})
    }
    property int second: box(4).value
    onSecondChanged: {
        box(4).value = second
        second = Qt.binding(function(){return box(4).value})
    }

    property CircularSpinBox dayLink: circularLink

    boxes: Row {
        NumberBox {
            id: hourBox
            from: 0
            to: 23
            value: (new Date).getHours()
            circularLink: dayLink
        }
        EnumBox {
            enabled: false
            from:0;to:0;valueTexts:[":"]
        }
        NumberBox {
            id: minuteBox
            from: 0
            to: 59
            digitCount: 2
            value: (new Date).getMinutes()
            circularLink: hourBox
        }
        EnumBox {
            enabled: false
            from:0;to:0;valueTexts:[":"]
        }
        NumberBox {
            id: secondBox
            from: 0
            to: 59
            digitCount: 2
            value: (new Date).getSeconds()
            circularLink: minuteBox
        }
    }
    function setTime(hour,minute,second)
    {
        box(0).value = hour
        box(2).value = minute
        box(4).value = second
    }
    function setCurrent()
    {
        var current = new Date
        setTime(current.getHours(), current.getMinutes(), current.getSeconds())
    }
    Component.onCompleted: {
        setCurrent()
    }
}
