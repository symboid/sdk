
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

IndirectContainer {
    height: column.height
    container: toolBar
    Column {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right

        ToolBar {
            id: toolBar
            anchors.left: parent.left
            anchors.right: parent.right
            Material.primary: "#95B2A0"
        }

        Repeater {
            model: 3
            delegate: Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 2
                readonly property var flagColor: [ "red", "white", "green" ]
                color: flagColor[index]
            }
        }
    }
}
