
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

            Column {
                spacing: itemPane.padding
                Row {
                    ItemSlot {
                        item: setting
                        width: cellWidth - infoButton.width
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
                        ColorOverlay {
                            anchors.fill: parent
                            source: parent
                            color: "gray"
                        }
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
