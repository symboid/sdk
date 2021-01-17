
import QtQuick 2.12
import QtQuick.Controls 2.5

LoadListItem {
    property alias editText: itemNameEdit.text
    signal editAccepted
    signal editCanceled

    mainItem: Item {
        TextField {
            id: itemNameEdit
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            onAccepted: editAccepted()
            Keys.onEscapePressed: editCanceled()
        }
    }
}
