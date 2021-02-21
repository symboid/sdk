
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

ControlListTreeNode {
    property Item mainItem: Item {}
    property alias leftItem: leftItemSlot.contentItem
    property Item rightItem: hint !== "" ? infoItem : emptyItem
    property alias background: itemPane.background
    readonly property int defaultItemHeight: metrics.height
    property int cellWidth: Math.min(400, rowWidth - 2*mainRow.spacing)
    readonly property int rowWidth: parent !== null ? parent.width : 0
    property alias hint: hintLabel.text
    property bool indented: false
    property bool withSeparator: false
    property alias lineColor: line.color
    property bool revertedLayout: false
    readonly property alias leftItemSpace: leftItemSlot.width

    property Item metrics: RoundButton {}
    property Item emptyItem: Item {}
    property Item infoItem: RoundButton {
        id: infoButton
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
            layoutDirection: revertedLayout ? Qt.RightToLeft : Qt.LeftToRight

            ItemSlotExpanding {
                id: leftItemSlot
                anchors.verticalCenter: parent.verticalCenter
                contentItem: Item {
                    height: 1
                    width: indented ? defaultItemHeight/2 : 0
                }
            }

            ItemSlot {
                id: itemSlot
                anchors.verticalCenter: parent.verticalCenter
                contentItem: mainItem
                width: cellWidth - (leftItemSlot.width > 0 ? leftItemSlot.width + parent.spacing : 0)
                - (rightItemSlot.width > 0 ? rightItemSlot.width + parent.spacing : 0)
            }
            ItemSlot {
                id: rightItemSlot
                anchors.verticalCenter: parent.verticalCenter
                contentItem: rightItem
                showFrame: true
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
        id: line
        anchors.horizontalCenter: parent.horizontalCenter
        width: rowWidth
        height: withSeparator ? 2 : 1
        color: withSeparator ? "darkgray" : "lightgray"
    }
}
