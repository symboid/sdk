
import QtQuick 2.12

MultiNumberBox {

    property int year: box(0).value
    property int month: box(1).value
    property int day: box(2).value

    boxes: Row {
        NumberBox {
            id: yearBox
            from: -3000
            to: 3000
            displaySuffix: "."
        }
        NumberBox {
            id: monthBox
            from: 1
            to: 12
            displaySuffix: "."
            circularLink: yearBox
        }
        NumberBox {
            id: dayBox
            from: 1
            to: {
                switch (monthBox.value)
                {
                case 2: return isLeapYear() ? 29 : 28
                case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31
                                                                 default: return 30
                }
            }
            displaySuffix: "."
        }
    }
    function isLeapYear()
    {
        return year % 4 === 0 && (year % 100 !== 0 || year % 400 === 0)
    }
    property NumberBox dayLink: box(2)

    Component.onCompleted: {
        var current = new Date
        box(0).value = current.getFullYear()
        box(1).value = current.getMonth() + 1
        box(2).value = current.getDate()
    }
}
