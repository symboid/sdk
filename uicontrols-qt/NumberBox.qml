
import QtQuick 2.12

NumericBox {

    value: 0

    property string displaySuffix: ""

    textFromValue: function(value, locale)
    {
        return String(value) + displaySuffix
    }
    valueFromText: function(text, locale)
    {
        var suffixPos = String(text).indexOf(displaySuffix)
        var valueString = (suffixPos !== 0) ? String(text).substring(0, suffixPos) : text
        return Number(valueString)
    }
    validator: RegExpValidator {
        regExp: new RegExp("[0-9]*" + displaySuffix)
    }
}
