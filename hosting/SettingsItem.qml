
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import QtGraphicalEffects 1.0

Column {
    property Item setting: Item {}
    property Item leftItem: Item {}
    property Item rightItem: hint !== "" ? infoButton : emptyItem
    property alias background: itemPane.background
    readonly property int cellWidth: 400
    readonly property int rowWidth: parent.width

    property alias hint: hintLabel.text

    property Item emptyItem: Item {}
    property Item infoButton: Image {
        source: "/icons/info_icon&24.png"
        height: 24
        width: 24
        property bool checked: false
        MouseArea {
            anchors.fill: parent
            onClicked: parent.checked = !parent.checked
        }
        opacity: 0.25
        smooth: true
    }

    Pane {
        id: itemPane
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        Row {
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
                ItemSlot {
                    id: settingSlot
                    item: setting
                    width: cellWidth
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
