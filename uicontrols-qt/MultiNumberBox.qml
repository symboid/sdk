
import QtQuick 2.12
import QtQuick.Controls 2.5

Row {
    property bool editable: false
    property bool circular: false
    property CircularSpinBox circularLink: null
    property Component boxes: null

    Loader {
        id: boxesLoader
        sourceComponent: boxes
        active: boxes !== null
        onSourceComponentChanged: {
            for (var b = 0; b < item.children.length; ++b)
            {
                var box = item.children[b]
                if (box instanceof NumericBox)
                {
                    box.editable = editable
                }
            }
        }
    }
    property Item numBoxes: boxesLoader.item
    readonly property int boxCount: numBoxes !== null ? numBoxes.children.length : 0
    function box(boxIndex)
    {
        return numBoxes !== null && 0 <= boxIndex && boxIndex < boxCount ? numBoxes.children[boxIndex] : null
    }

    Item { width:10; height:1; visible: editable }

    RoundButton {
        id: popupButton
        height: numBoxes.height
        width: height
        visible: editable
        text: "..."
        onClicked: !popupItem.visible ? popupItem.open() : popupItem.close()
    }

    Popup {
        id: popupItem

        property int visibleCount: 3

        padding: 1
        width: numBoxes.width+2*padding
        height: visibleCount * numBoxes.height
        x: -1
        y: -(visibleCount / 2 - 0.5) * numBoxes.height

        Row {
            anchors.fill: parent
            Repeater {
                model: boxCount
                delegate: Tumbler {
                    readonly property NumericBox inputNumber: box(index)
                    height: parent.height
                    width: inputNumber.width

                    model: inputNumber.to - inputNumber.from + 1
                    wrap: true
                    currentIndex: inputNumber.value - inputNumber.from
                    visibleItemCount: popupItem.visibleCount

                    onVisibleChanged: {
                        if (!visible && inputNumber !== null)
                        {
                            inputNumber.value = inputNumber.from + currentIndex
                        }
                    }

                    delegate: Text {
                        width: inputNumber.width
                        height: inputNumber.height
                        text: inputNumber.textFromValue(inputNumber.from + modelData, Qt.locale())
                        font: inputNumber.font
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        opacity: 1.0 - Math.abs(Tumbler.displacement) / visibleItemCount
                    }
                }
            }
        }
    }
}
