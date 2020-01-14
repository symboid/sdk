
import QtQuick 2.12
import QtQuick.Controls 2.5

Row {
    id: multiNumberBox
    property bool editable: false
    property bool circular: false
    property CircularSpinBox circularLink: null
    property ListModel boxes: null
    property alias numberBoxes: numbers
    Repeater {
        id: numbers
        model: boxes
        delegate: Loader {
            Component {
                id: numberBoxComponent
                NumberBox {
                    editable: multiNumberBox.editable
                    circular: multiNumberBox.circular
                    circularLink: !circular ? null :
                                  index > 0 ? numbers.itemAt(index-1).item :
                                              multiNumberBox.circularLink

                    from: number_from
                    to: number_to
                    displaySuffix: number_suffix            }
            }
            Component {
                id: enumBoxComponent
                EnumBox {
                    editable: multiNumberBox.editable
                    circular: multiNumberBox.circular
                    circularLink: !circular ? null :
                                  index > 0 ? numbers.itemAt(index-1).item :
                                              multiNumberBox.circularLink
                    from: number_from
                    to: number_to
                }
            }

            sourceComponent: is_enum ? enumBoxComponent : numberBoxComponent
            active: true
        }
    }
    NumberBox {
        id: nullNumberBox
        visible: false
    }
    function numberBox(index)
    {
        return numberBoxes.count > index ? numberBoxes.itemAt(index).item : nullNumberBox
    }
    readonly property int numbersWidth: {
        var width = 0
        for (var b = 0; b < numberBoxes.count; ++b)
        {
            width += numberBoxes.itemAt(b).item.width
        }
        return width
    }
    readonly property int numbersHeight: numberBox(0).height

    Item { width:10; height:1; visible: editable }

    RoundButton {
        id: popupButton
        height: numbersHeight
        width: height
        visible: editable
        text: "..."
        onClicked: !popupItem.visible ? popupItem.open() : popupItem.close()
    }

    Popup {
        id: popupItem

        property int visibleCount: 3

        padding: 1
        width: numbersWidth+2*padding
        height: visibleCount * numbersHeight
        x: -1
        y: -(visibleCount / 2 - 0.5) * numbersHeight

        Row {
            anchors.fill: parent
            Repeater {
                model: boxes
                delegate: Tumbler {
                    readonly property NumericBox inputNumber: numberBox(index)
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
