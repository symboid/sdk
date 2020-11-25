
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

SettingsTreeNode {
    property Item setting: Item {}
    property Item leftItem: Item { height: defaultItemHeight; width: indented ? defaultItemHeight : 0 }
    property Item rightItem: hint !== "" ? infoItem : emptyItem
    property alias background: itemPane.background
    readonly property int defaultItemHeight: metrics.height
    readonly property int cellWidth: Math.min(400, parent.width - 2*settingRow.spacing)
    readonly property int rowWidth: parent.width

    property alias hint: hintLabel.text
    property bool indented: false

    property Item metrics: RoundButton {}
    property Item emptyItem: Item {}
    property Item infoItem: Item {
        width: defaultItemHeight
        height: defaultItemHeight
        Image {
            id: infoButton
            anchors.centerIn: parent
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
    }

    Pane {
        id: itemPane
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        Row {
            id: settingRow
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            ItemSlot {
                id: leftItemSlot
                anchors.verticalCenter: parent.verticalCenter
                item: leftItem
            }
            Column {
                id: itemColumn
                anchors.verticalCenter: parent.verticalCenter
                spacing: itemPane.padding
                ItemSlot {
                    id: settingSlot
                    item: setting
                    width: cellWidth - (leftItemSlot.width > 0 ? leftItemSlot.width + parent.spacing : 0)
                    - (rightItemSlot.width > 0 ? rightItemSlot.width + parent.spacing : 0)
                }
                Rectangle {
                    height: 1
                    width: settingSlot.width
                    color: "lightgray"
                    visible: hintLabel.visible
                }

                Label {
                    id: hintLabel
                    visible: infoButton.checked
                    horizontalAlignment: Label.AlignRight
                    width: settingSlot.width
                    wrapMode: Text.WordWrap
                    text: hint
                    font.italic: true
                }
            }
            ItemSlot {
                id: rightItemSlot
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
