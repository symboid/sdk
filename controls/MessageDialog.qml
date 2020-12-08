
import QtQuick 2.12
import QtQuick.Controls 2.5

Dialog {
    property alias message: messageLabel.text
    width: parent.width
    contentItem: Label {
        id: messageLabel
        width: parent.width
        horizontalAlignment: Label.AlignHCenter
    }
    footer: DialogButtonBox {
        id: buttonBox
        alignment: Qt.AlignHCenter
    }
}
