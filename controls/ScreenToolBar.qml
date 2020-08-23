
import QtQuick 2.12
import QtQuick.Controls 2.5

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
