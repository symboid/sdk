
import QtQuick 2.12

NumericBox {

    property var valueTexts: null
    value: from

    textFromValue: function(value, locale)
    {
        return valueTexts !== null && from <= value && value <= to ? valueTexts[value - from] : "?"
    }
    valueFromText: function(text, locale)
    {
        if (valueTexts !== null)
        {
            for (var v = from; v <= to; ++v)
            {
                if (valueTexts[v - from] === text)
                {
                    return Number(v)
                }
            }
        }
        return Number(from)
    }
    validator: RegExpValidator {
        regExp: {
            var regExpStr = "("
            if (valueTexts !== null)
            {
                for (var v = from; v <= to; ++v)
                {
                    regExpStr += valueTexts[v - from]
                    regExpStr += "|"
                }
            }
            regExpStr += ")"
            return new RegExp(regExpStr)
        }
    }
}
