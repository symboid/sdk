
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0

Drawer {

    DocItemOpsView {
        anchors.fill: parent
        leftAligned: edge === Qt.LeftEdge
        operations: [
            InputOperation {
                title: qsTr("Recent horoscopes")
                control: Rectangle {
                    width: 100
                    height: 100
                    border.width: 1
                    border.color: "red"
                }
            },
            InputOperation {
                title: qsTr("Current transit")
            },
            InputOperation {
                title: qsTr("Saved horoscopes")
                control: Rectangle {
                    width: 100
                    height: 100
                    border.width: 1
                    border.color: "blue"
                }
            }
        ]
    }
}
