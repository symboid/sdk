
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

ControlListTreeNode {
    property Item mainItem: Item {}
    property Item rightItem: hint !== "" ? infoItem : emptyItem
    property alias background: itemPane.background
    readonly property int defaultItemHeight: metrics.height
    readonly property int cellWidth: Math.min(400, parent.width - 2*mainRow.spacing)
    readonly property int rowWidth: parent.width
    property alias hint: hintLabel.text
    property bool indented: false
    property bool withSeparator: false

    property Item metrics: RoundButton {}
    property Item emptyItem: Item {}
    property Item infoItem: RoundButton {
        id: infoButton
        anchors.centerIn: parent
        icon.source: "/icons/info_icon&24.png"
        checkable: true
        opacity: 0.25
        smooth: true
        background: null
    }

    Pane {
        id: itemPane
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        Row {
            id: mainRow
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Item {
                id: leftIndent
                anchors.verticalCenter: parent.verticalCenter
                height: 1
                width: indented ? defaultItemHeight/2 : 0
            }
            ItemSlot {
                id: itemSlot
                anchors.verticalCenter: parent.verticalCenter
                contentItem: mainItem
                width: cellWidth - (leftIndent.width > 0 ? leftIndent.width + parent.spacing : 0)
                - (rightItemSlot.width > 0 ? rightItemSlot.width + parent.spacing : 0)
            }
            ItemSlot {
                id: rightItemSlot
                anchors.verticalCenter: parent.verticalCenter
                contentItem: rightItem
            }
        }
    }
    HorizontalLine {
        anchors.horizontalCenter: parent.horizontalCenter
        width: itemSlot.width
        visible: hintLabel.visible
    }
    Pane {
        anchors.horizontalCenter: parent.horizontalCenter
        visible: infoButton.checked
        width: itemSlot.width
        contentItem: Label {
            id: hintLabel
            horizontalAlignment: Label.AlignRight
            wrapMode: Text.WordWrap
            text: hint
            font.italic: true
        }
    }
    HorizontalLine {
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        height: withSeparator ? 2 : 1
        color: withSeparator ? "darkgray" : "lightgray"
    }
}
