
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Hosting 1.0

SettingsItem {
    property alias text: radioButton.text
    property alias checked: radioButton.checked
    property alias enabled: radioButton.enabled
    property alias button: radioButton
    property ConfigNode enumConfig: null
    property int enumValue: 0

    setting: RadioButton {
        id: radioButton
        checked: enumConfig.value === enumValue
        onCheckedChanged: {
            if (checked)
            {
                enumConfig.value = enumValue
            }
        }
    }
}
