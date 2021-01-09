
import QtQuick 2.12

NumericBox {

    value: 0

    property string displaySuffix: ""
    property int digitCount: 1

    textFromValue: function(value, locale)
    {
        var text = String(value)
        while (text.length < digitCount)
        {
            text = "0" + text
        }
        return text + displaySuffix
    }
    valueFromText: function(text, locale)
    {
        var suffixPos = String(text).indexOf(displaySuffix)
        var valueString = (displaySuffix != "" && suffixPos !== -1) ? String(text).substring(0, suffixPos) : String(text)
        return Number(valueString)
    }
    validator: RegExpValidator {
        regExp: new RegExp("[0-9]*" + displaySuffix)
    }
}
