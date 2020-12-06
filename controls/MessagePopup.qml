
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Drawer {
    id: drawer

    property alias iconSource: messageIcon.icon.source
    property alias iconColor: messageIcon.icon.color
    property bool autoClose: false
    property bool showBusy: false

    property Item messageIndicator: Button {
        id: messageIcon
        icon.width: closeButton.width
        icon.height: closeButton.height
        width: closeButton.width
        height: closeButton.height
        background: null
    }

    edge: Qt.TopEdge
    dragMargin: 0
    width: parent.width
    height: messagePane.height
    closePolicy: showBusy ? Popup.NoAutoClose : Popup.CloseOnEscape | Popup.CloseOnPressOutside

    function show(message)
    {
        messageLabel.text = message
        open()
        if (autoClose)
        {
            closeTimer.start()
        }
    }

    Pane {
        id: messagePane
        background: null
        anchors.horizontalCenter: parent.horizontalCenter
        Row {
            spacing: messagePane.padding
            ItemSlot {
                id: messageIndicatorSlot
                anchors.verticalCenter: parent.verticalCenter
                item: messageIndicator
            }
            Label {
                id: messageLabel
                anchors.verticalCenter: parent.verticalCenter
                width: drawer.width - messageIndicatorSlot.width - closeButton.width - 4 * messagePane.padding
                font.italic: true
                wrapMode: Label.WordWrap
                horizontalAlignment: Label.AlignHCenter
            }
            RoundButton {
                id: closeButton
                anchors.verticalCenter: parent.verticalCenter
                icon.source: "/icons/delete_icon&32.png"
                icon.color: pressed ? drawer.background.color : "grey"
                onClicked: close()
                background: null
            }
        }
    }

    Timer {
        id: closeTimer
        interval: 2000
        onTriggered: close()
    }
}
