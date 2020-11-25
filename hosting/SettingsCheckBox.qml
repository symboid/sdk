
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Hosting 1.0

SettingsItem {
    property alias text: checkBox.text
    property alias checked: checkBox.checked
    property alias enabled: checkBox.enabled
    property ConfigNode configNode: null

    setting: CheckBox {
        id: checkBox
        text: configNode.title
        checked: configNode.value
        onCheckedChanged: {
            configNode.value = checked
            checked = Qt.binding(function(){return configNode.value})
        }
    }
}
