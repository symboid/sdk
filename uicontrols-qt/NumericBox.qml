
import QtQuick 2.12

CircularSpinBox {
    id: numericBox

    property CircularSpinBox circularLink: null

    onIncrementedCircular: {
        if (circularLink)
        {
            circularLink.increment()
        }
    }
    onDecrementedCircular: {
        if (circularLink)
        {
            circularLink.decrement()
        }
    }

    up.indicator: null
    down.indicator: null

    TextMetrics {
        id: numericBoxMetrics
        text: numericBox.textFromValue(numericBox.value, Qt.locale())
        font: numericBox.font
    }
    width: numericBoxMetrics.width + height*0.75

    MouseArea {
        anchors.fill: parent
        onWheel: {
            if (editable && wheel.angleDelta.y > 0)
            {
                numericBox.increment()
            }
            else if (editable)
            {
                numericBox.decrement()
            }
        }
    }
    Keys.onUpPressed: {
        if (editable)
        {
            numericBox.increment()
        }
    }
    Keys.onDownPressed: {
        if (editable) {
            numericBox.decrement()
        }
    }
}
