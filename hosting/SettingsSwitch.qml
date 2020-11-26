
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Hosting 1.0

SettingsItem {
    property alias text: label.text
    property alias checked: switchButton.checked
    property alias enabled: switchItem.enabled
    property ConfigNode configNode: null

    setting: Row {
        id: switchItem
        Label {
            id: label
            anchors.verticalCenter: parent.verticalCenter
            width: cellWidth - switchButton.width
        }
        Switch {
            id: switchButton
            anchors.verticalCenter: parent.verticalCenter
            checked: configNode.value
            onCheckedChanged: {
                configNode.value = checked
                checked = Qt.binding(function(){return configNode.value})
            }
        }
    }
}
