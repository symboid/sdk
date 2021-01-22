
import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
    property alias mainItem: mainItemSlot.item
    property alias leftItem: leftItemSlot.item
    property string itemTitle: ""
    property int itemWidth: 200
    property alias loadIconSource: loadButton.icon.source
    property alias lineColor: line.color
    property bool revertedLayout: false
    readonly property alias leftItemSpace: leftPane.width
    readonly property alias loadButtonSpace: loadButtonPane.width
    readonly property int mainItemSpace: itemWidth - leftItemSpace - loadButtonSpace
    signal itemClicked
    signal buttonClicked

    function setEditFocus()
    {
        itemNameEdit.focus = true
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        height: itemRow.height
        onClicked: itemClicked()
        onDoubleClicked: buttonClicked()

        Row {
            id: itemRow
            layoutDirection: revertedLayout ? Qt.RightToLeft : Qt.LeftToRight
            anchors.horizontalCenter: parent.horizontalCenter
            Pane {
                id: leftPane
                anchors.verticalCenter: parent.verticalCenter
                background: null
                contentItem: ItemSlot {
                    id: leftItemSlot
                }
            }
            ItemSlot {
                id: mainItemSlot
                anchors.verticalCenter: parent.verticalCenter
                width: mainItemSpace

                item: Label {
                    elide: Text.ElideRight
                    text: itemTitle
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Pane {
                id: loadButtonPane
                anchors.verticalCenter: parent.verticalCenter
                background: null
                contentItem: RoundButton {
                    id: loadButton
                    icon.source: revertedLayout ? "/icons/br_prev_icon&24.png" : "/icons/br_next_icon&24.png"
                    visible: icon.source !== ""
                    onClicked: buttonClicked()
                }
            }
        }
    }

    HorizontalLine {
        id: line
        anchors.left: parent.left
        anchors.right: parent.right
        color: "lightgray"
    }
}
