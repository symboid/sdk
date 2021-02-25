
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

FolderItem {
    property alias text: checkBox.text
    property alias checked: checkBox.checked
    property alias enabled: checkBox.enabled
    property ConfigNode configNode: null

    mainItem: CheckBox {
        id: checkBox
        checked: configNode.value
        onCheckedChanged: {
            configNode.value = checked
            checked = Qt.binding(function(){return configNode.value})
        }
    }
}
