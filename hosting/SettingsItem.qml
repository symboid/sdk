
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import QtGraphicalEffects 1.0

Column {
    property Item setting: Item {}
    property Item leftItem: Item {}
    property Item rightItem: Item {}
    property alias background: itemPane.background
    readonly property int cellWidth: 400
    readonly property int rowWidth: parent.width

    property alias hint: hintLabel.text

    Pane {
        id: itemPane
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        Grid {
            rows: 1
            columns: 6
            columnSpacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            verticalItemAlignment: Grid.AlignVCenter

            Item {
                height: 1
                width: (rowWidth - cellWidth) / 2 - leftItemSlot.width
                       - (leftItemSlot.width > 0 ? 3 : 2) * parent.columnSpacing
            }
            ItemSlot {
                id: leftItemSlot
                item: leftItem
            }
            Item {
                width:1;
                height: parent.height
            }
            Column {
                id: settingColumn
                spacing: itemPane.padding
                Row {
                    ItemSlot {
                        item: setting
                        width: cellWidth - (infoButton.visible ? infoButton.width : 0)
                    }
                    Image {
                        id: infoButton
                        visible: hint !== ""
                        anchors.verticalCenter: parent.verticalCenter
                        source: "/icons/info_icon&24.png"
                        property bool checked: false
                        MouseArea {
                            anchors.fill: parent
                            onClicked: parent.checked = !parent.checked
                        }
                        smooth: true
                    }
                }
                Rectangle {
                    height: 1
                    width: cellWidth
                    color: "lightgray"
                    visible: hintLabel.visible
                }
                Label {
                    id: hintLabel
                    visible: infoButton.checked
                    horizontalAlignment: Label.AlignRight
                    width: cellWidth
                    wrapMode: Text.WordWrap
                    text: hint
                    font.italic: true
                }
            }
            Rectangle {
                width:1;
                height: parent.height
                color: "lightgray"
            }
            ItemSlot {
                id: rightItemSlot
                item: rightItem
            }
            Item {
                height: 1
                width: (rowWidth - cellWidth) / 2 - rightItemSlot.width
                       - (rightItemSlot.width > 0 ? 3 : 2) * parent.columnSpacing
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
