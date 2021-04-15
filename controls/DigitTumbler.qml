
import QtQuick 2.12
import QtQuick.Controls 2.5

Tumbler {
    property int base: 10
    model: base
    readonly property int digitWidth: String(base-1).length
    property bool withLeadingZeros: digitWidth > 1

    readonly property int minDigit: 0
    readonly property int maxDigit: base - 1
    readonly property int currentValue: currentIndex < 0 ? 0 : currentIndex
    function increment()
    {
        currentIndex = currentIndex === maxDigit ? minDigit : currentIndex + 1
    }
    function decrement()
    {
        currentIndex = currentIndex === minDigit ? maxDigit : currentIndex - 1
    }
    function fillLeadingZeros(d)
    {
        return ""+~~(d/10)+(d%10)
    }

    delegate: Label {
        text: withLeadingZeros ? fillLeadingZeros(index) : index
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        opacity: 1.0 - Math.abs(Tumbler.displacement) / (visibleItemCount / 2)
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
}
