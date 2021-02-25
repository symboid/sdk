
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

ControlListTreeNode {
    property alias mainItem: mainItemSlot.contentItem
    property alias leftItem: leftItemSlot.contentItem
    property Item rightItem: hint !== "" ? infoItem : emptyItem

    property alias title: mainTitle.text
    property alias titleAlignment: mainTitle.horizontalAlignment

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
        background: null
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
                    width: indented ? metrics.height/2 : 0
                }
            }

            ItemSlot {
                id: mainItemSlot
                anchors.verticalCenter: parent.verticalCenter
                width: cellWidth - (leftItemSlot.width > 0 ? leftItemSlot.width + parent.spacing : 0)
                - (rightItemSlot.width > 0 ? rightItemSlot.width + parent.spacing : 0)
                contentItem: Label {
                    id: mainTitle
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
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
        width: mainItemSlot.width
        visible: hintLabel.visible
    }
    Pane {
        anchors.horizontalCenter: parent.horizontalCenter
        visible: infoButton.checked
        width: mainItemSlot.width
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
