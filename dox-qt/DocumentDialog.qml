
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0

Drawer {

    DocItemOpsView {
        anchors.fill: parent
        leftAligned: edge === Qt.LeftEdge
        operations: [
            DocItemOp {
                title: qsTr("Recent horoscopes")
                control: Rectangle {
                    width: 100
                    height: 100
                    border.width: 1
                    border.color: "red"
                }
            },
            DocItemOp {
                title: qsTr("Current transit")
            },
            DocItemOp {
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
