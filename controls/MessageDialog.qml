
import QtQuick 2.12
import QtQuick.Controls 2.5

Drawer {
    id: dialog

    edge: Qt.TopEdge
    dragMargin: 0
    width: parent.width
    height: messagePane.height

    function showNotification(message)
    {
        messageLabel.text = message
        open()
    }

    function showError(message)
    {
        messageLabel.text = message
        open()
    }

    Pane {
        id: messagePane
        background: null
        anchors.horizontalCenter: parent.horizontalCenter
        Pane {
            background: null
            anchors.horizontalCenter: parent.horizontalCenter
            Row {
                spacing: messagePane.padding
                Image {
                    id: messageIcon
                    anchors.verticalCenter: parent.verticalCenter
                    source: "file:///Users/robert/Munka/icons/black/png/info_icon&32.png"
                }
                Label {
                    id: messageLabel
                    anchors.verticalCenter: parent.verticalCenter
                    width: dialog.width - messageIcon.width - closeButton.width - 6 * messagePane.padding
                    font.italic: true
                    wrapMode: Label.WordWrap
                    horizontalAlignment: Label.AlignHCenter
                }
                RoundButton {
                    id: closeButton
                    anchors.verticalCenter: parent.verticalCenter
                    icon.source: "file:///Users/robert/Munka/icons/black/png/delete_icon&32.png"
                    icon.color: pressed ? "white" : "black"
                    onClicked: close()
                }
            }
        }
    }
}
