
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

FolderItem {

    property alias checked: switchButton.checked
    property ConfigNode configNode: null

    rightItem: Switch {
        id: switchButton
        checked: configNode.value
        onCheckedChanged: {
            configNode.value = checked
            checked = Qt.binding(function(){return configNode.value})
        }
    }
}
