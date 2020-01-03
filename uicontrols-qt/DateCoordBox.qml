
import QtQuick 2.12

MultiNumberBox {

    property int year: numberBox(0).value
    property int month: numberBox(1).value
    property int day: numberBox(2).value
    circular: true

    boxes: ListModel {
        ListElement {
            number_from: -3000
            number_to: 3000
            number_suffix: "."
        }
        ListElement {
            number_from: 1
            number_to: 12
            number_suffix: "."
        }
        ListElement {
            number_from: 1
            number_to: 31
            number_suffix: "."
        }
    }
    function isLeapYear()
    {
        return year % 4 === 0 && (year % 100 !== 0 || year % 400 === 0)
    }
    Component.onCompleted: {
        var current = new Date
        numberBox(0).value = current.getFullYear()
        numberBox(1).value = current.getMonth() + 1
        numberBox(2).value = current.getDate()

        numberBox(2).to = Qt.binding(function(){
            switch (month)
            {
            case 2: return isLeapYear() ? 29 : 28
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31
                                                             default: return 30
            }
        })
    }
    property NumberBox dayLink: numberBox(2)
}
