
import QtQuick 2.12
import QtQuick.Controls 2.5

Tumbler {
    property int base: 10
    model: base

    readonly property int minDigit: 0
    readonly property int maxDigit: base - 1
    function increment()
    {
        currentIndex = currentIndex === maxDigit ? minDigit : currentIndex + 1
    }
    function decrement()
    {
        currentIndex = currentIndex === minDigit ? maxDigit : currentIndex - 1
    }
    MouseArea {
        anchors.fill: parent
        onWheel: {
            if (wheel.angleDelta.y > 0)
            {
                increment()
            }
            else
            {
                decrement()
            }
        }
    }

    property DigitTumbler circularLink: null
    property int prevCurrentIndex: -1
    onCurrentIndexChanged: {
        if (circularLink !== null)
        {
            if (currentIndex === minDigit && prevCurrentIndex === maxDigit)
            {
                circularLink.increment()
            }
            else if (currentIndex === maxDigit && prevCurrentIndex === minDigit)
            {
                circularLink.decrement()
            }
        }

        prevCurrentIndex = currentIndex
    }
}
