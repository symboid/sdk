
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Column {
    property alias itemTitle: itemNameEdit.text
    property int itemWidth: 200
    property alias loadIconSource: loadButton.icon.source
    property alias selectIndicator: selected.indicator
    property alias lineColor: line.color
    property bool editable: true
    property bool selectable: false
    property bool revertedLayout: false
    signal itemClicked
    signal buttonClicked
    signal editAccepted

    function setEditFocus()
    {
        itemNameEdit.focus = true
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        height: loadButtonPane.height
        onClicked: itemClicked()

        Row {
            layoutDirection: revertedLayout ? Qt.RightToLeft : Qt.LeftToRight
            anchors.horizontalCenter: parent.horizontalCenter
            Pane {
                id: selectedPane
                anchors.verticalCenter: parent.verticalCenter
                background: null
                CheckBox {
                    id: selected
                    visible: selectable || checked
                }
            }
            StackLayout {
                anchors.verticalCenter: parent.verticalCenter
                currentIndex: editable
                width: itemWidth - selectedPane.width - loadButtonPane.width

                Text {
                    elide: Text.ElideRight
                    text: itemTitle
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: itemNameEdit.leftPadding
                    rightPadding: itemNameEdit.rightPadding
                }

                TextField {
                    id: itemNameEdit
                    verticalAlignment: Text.AlignVCenter
                    onAccepted: editAccepted()
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
