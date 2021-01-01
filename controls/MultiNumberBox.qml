
import QtQuick 2.12
import QtQuick.Controls 2.5

Pane {
    property bool editable: false
    property bool circular: false
    property CircularSpinBox circularLink: null
    property Component boxes: null

    property Item numBoxes: boxesLoader.item
    readonly property int boxCount: numBoxes !== null ? numBoxes.children.length : 0
    function box(boxIndex)
    {
        return numBoxes !== null && 0 <= boxIndex && boxIndex < boxCount ? numBoxes.children[boxIndex] : null
    }

    Row {
        Loader {
            id: boxesLoader
            sourceComponent: boxes
            active: boxes !== null
            anchors.verticalCenter: parent.verticalCenter
            readonly property int borderWidth: item !== undefined && item.children.length > 0 &&
                                               item.children[0].background.border !== undefined ?
                                               item.children[0].background.border.width: 0
            onSourceComponentChanged: {
                item.spacing = -borderWidth
                for (var b = 0; b < item.children.length; ++b)
                {
                    var box = item.children[b]
                    if (box instanceof NumericBox)
                    {
                        box.editable = editable
                    }
                }
            }
            Popup {
                id: popupItem

                property int visibleCount: 4

                padding: 1
                width: 2*numBoxes.width+2*padding
                height: visibleCount * numBoxes.height
                anchors.centerIn: parent

                Row {
                    anchors.fill: parent
                    Repeater {
                        model: boxCount
                        delegate: Tumbler {
                            readonly property NumericBox inputNumber: box(index)
                            height: parent.height
                            width: inputNumber.width * 2
                            enabled: inputNumber.enabled
                            visible: inputNumber.visible

                            model: inputNumber.model
                            wrap: true
                            currentIndex: inputNumber.value - inputNumber.from
                            onCurrentIndexChanged: {
                                if (currentIndex < inputNumber.to - inputNumber.from + 1)
                                {
                                    inputNumber.value = inputNumber.from + currentIndex
                                }
                                else
                                {
                                    var correctPosition = (prevIndex === 0) ?
                                                inputNumber.to - inputNumber.from : 0
                                    this.positionViewAtIndex(correctPosition, Tumbler.Center)
                                }
                                prevIndex = currentIndex
                            }
                            property int prevIndex: -1

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
                                visible: modelData < (inputNumber.to - inputNumber.from + 1)
                                font.bold: Math.abs(Tumbler.displacement) < 0.5
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                opacity: 1.0 - Math.abs(Tumbler.displacement) / visibleItemCount
                            }
                        }
                    }
                }
            }
        }

        Item { width:10; height:1; visible: editable }

        RoundButton {
            id: popupButton
            anchors.verticalCenter: parent.verticalCenter
            width: height
            visible: editable
            text: "..."
            onClicked: !popupItem.visible ? popupItem.open() : popupItem.close()
        }
    }
}
