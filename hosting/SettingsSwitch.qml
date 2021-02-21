
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Hosting 1.0

SettingsItem {
    property alias text: label.text
    property alias checked: switchButton.checked
    property ConfigNode configNode: null

    mainItem: Label {
        id: label
        width: cellWidth - switchButton.width
    }
    rightItem: Switch {
        id: switchButton
        anchors.verticalCenter: parent.verticalCenter
        checked: configNode.value
        onCheckedChanged: {
            configNode.value = checked
            checked = Qt.binding(function(){return configNode.value})
        }
    }
}
