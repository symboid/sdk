
import QtQuick 2.12

MultiNumberBox {

    property int year: box(0).value
    onYearChanged: {
        box(0).value = year
        year = Qt.binding(function(){return box(0).value})
    }
    property int month: box(1).value
    onMonthChanged: {
        box(1).value = month
        month = Qt.binding(function(){return box(1).value})
    }
    property int day: box(2).value
    onDayChanged: {
        box(2).value = day
        day = Qt.binding(function(){return box(2).value})
    }

    boxes: Row {
        NumberBox {
            id: yearBox
            from: -3000
            to: 3000
            displaySuffix: "."
        }
        NumericBox {
            id: monthBox
            from: 1
            to: 12

            textFromValue: function(value, locale)
            {
                return (new Date(2000, value - 1, 1)).toLocaleDateString(locale, "MMMM")
            }
            valueFromText: function(text, locale)
            {
                var monthDate = Date.fromLocaleDateString(locale, "???", "")
                var formatStr = ""
                for (var f = 0; monthDate.toString()==="Invalid Date" && f<4; ++f)
                {
                    formatStr += "M"
                    monthDate = Date.fromLocaleDateString(locale, text, formatStr)
                }
                return monthDate.getMonth() + 1
            }
            validator: RegExpValidator {
                regExp: new  RegExp(monthRegExp())
                function monthRegExp()
                {
                    var regExpStr = "("
                    for (var m = 0; m < 12; ++m)
                    {
                        var monthDate = new Date(2000, m, 1)
                        var formatStr = ""
                        for (var l = 0; l < 4; ++l)
                        {
                            formatStr += "M"
                            regExpStr += monthDate.toLocaleDateString(Qt.locale(), formatStr)
                            regExpStr += "|"
                        }
                    }
                    regExpStr += ")"
                    return regExpStr
                }
            }
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
            circularLink: monthBox
        }
    }
    function isLeapYear()
    {
        return year % 4 === 0 && (year % 100 !== 0 || year % 400 === 0)
    }
    property NumberBox dayLink: box(2)

    function setDate(year,month,day)
    {
        box(0).value = year
        box(1).value = month
        box(2).value = day
    }
    function setCurrent()
    {
        var current = new Date
        setDate(current.getFullYear(), current.getMonth()+1, current.getDate())
    }
}
