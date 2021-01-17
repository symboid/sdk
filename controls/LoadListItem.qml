
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Column {
    property alias mainItem: mainItemSlot.item
    property alias rightItem: rightItemSlot.item
    property string itemTitle: ""
    property int itemWidth: 200
    property alias loadIconSource: loadButton.icon.source
    property alias lineColor: line.color
    property bool revertedLayout: false
    signal itemClicked
    signal buttonClicked

    function setEditFocus()
    {
        itemNameEdit.focus = true
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        height: loadButtonPane.height
        onClicked: itemClicked()
        onDoubleClicked: buttonClicked()

        Row {
            layoutDirection: revertedLayout ? Qt.RightToLeft : Qt.LeftToRight
            anchors.horizontalCenter: parent.horizontalCenter
            Pane {
                id: rightPane
                anchors.verticalCenter: parent.verticalCenter
                height: loadButtonPane.height
                width: loadButtonPane.height
                background: null
                ItemSlot {
                    id: rightItemSlot
                }
            }
            ItemSlot {
                id: mainItemSlot
                anchors.verticalCenter: parent.verticalCenter
                height: loadButtonPane.height
                width: itemWidth - rightPane.width - loadButtonPane.width

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
                RoundButton {
                    id: loadButton
                    icon.source: revertedLayout ? "/icons/br_prev_icon&24.png" : "/icons/br_next_icon&24.png"
                    visible: icon.source !== ""
                    onClicked: buttonClicked()
                }
            }
        }
    }

    Rectangle {
        id: line
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "lightgray"
    }
}
