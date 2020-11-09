
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Column {
    property Item setting: Item {}
    property Item leftItem: Item {}
    property Item rightItem: Item {}
    property alias background: itemPane.background
    readonly property int cellWidth: 400
    readonly property int rowWidth: parent.width


    property string hint: ""
    property Label hintLabel: Label {
        wrapMode: Text.WordWrap
        text: hint
    }

    Pane {
        id: itemPane
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        Grid {
            rows: 1
            columns: 5
            columnSpacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            verticalItemAlignment: Grid.AlignVCenter

            Item {
                height: 1
                width: (rowWidth - cellWidth)/2 - leftItemSlot.width
            }
            ItemSlot {
                id: leftItemSlot
                item: leftItem
            }

            ItemSlot {
                item: setting
                width: cellWidth
            }

            ItemSlot {
                id: rightItemSlot
                item: rightItem
            }
            Item {
                height: 1
                width: (rowWidth - cellWidth)/2 - rightItemSlot.width
            }
        }
    }
    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        height: 1
        color: "lightgray"
    }
}
