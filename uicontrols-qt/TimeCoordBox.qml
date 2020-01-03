
import QtQuick 2.12

MultiNumberBox {

    property int hour: numberBox(0).value
    property int minute: numberBox(1).value
    property int second: numberBox(2).value
    circular: true

    boxes: ListModel {
        ListElement {
            number_from: 0
            number_to: 23
            number_suffix: qsTr("h")
        }
        ListElement {
            number_from: 0
            number_to: 59
            number_suffix: qsTr("m")
        }
        ListElement {
            number_from: 0
            number_to: 59
            number_suffix: qsTr("s")
        }
    }
    Component.onCompleted: {
        var current = new Date
        numberBox(0).value = current.getHours()
        numberBox(1).value = current.getMinutes()
        numberBox(2).value = current.getSeconds()
    }
}
