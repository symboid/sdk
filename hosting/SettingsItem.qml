
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import QtGraphicalEffects 1.0

Column {
    property Item setting: Item {}
    property Item leftItem: Item {}
    property Item rightItem: Item {}
    property alias background: itemPane.background
    readonly property int cellWidth: Math.min(400, parent.width - 2*settingRow.sideItemSpace)
    readonly property int rowWidth: parent.width

    property alias hint: hintLabel.text

    Pane {
        id: itemPane
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        Row {
            id: settingRow
            readonly property int sideItemSpace: height + 3*spacing + 1
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: (rightItemSlot.width - leftItemSlot.width) / 2
                    + (rightItemSlot.width > 0)*5 - (leftItemSlot.width > 0)*5

            ItemSlot {
                id: leftItemSlot
                anchors.verticalCenter: parent.verticalCenter
                item: leftItem
            }
            Item {
                width: 1
                height: 1
            }
            Column {
                id: itemColumn
                anchors.verticalCenter: parent.verticalCenter
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
                        height: 24
                        property bool checked: false
                        MouseArea {
                            anchors.fill: parent
                            onClicked: parent.checked = !parent.checked
                        }
                        opacity: 0.25
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
                width: 1
                height: Math.max(leftItemSlot.height,itemColumn.height, rightItemSlot.height)
                color: "lightgray"
            }
            ItemSlot {
                id: rightItemSlot
                anchors.verticalCenter: parent.verticalCenter
                item: rightItem
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
