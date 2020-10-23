
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Column {
    property ListView listView: null
    property string itemTitle: ""
    property int itemWidth: 200
    property alias loadIconSource: loadButton.icon.source
    property alias lineColor: line.color
    property bool editable: true
    property bool selectable: false
    signal itemClicked

    function setEditFocus()
    {
        docNameEdit.focus = true
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        height: loadButtonPane.height
        onClicked: itemClicked()

        Row {
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
                id: docNameContainer
                anchors.verticalCenter: parent.verticalCenter
                currentIndex: editable
                width: itemWidth - selectedPane.width - loadButtonPane.width

                Text {
                    elide: Text.ElideRight
                    text: docNameEdit.text
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: docNameEdit.leftPadding
                    rightPadding: docNameEdit.rightPadding
                }

                TextField {
                    id: docNameEdit
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
                    visible: icon.source != ""
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
