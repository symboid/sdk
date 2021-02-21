
import QtQuick 2.12
import QtQuick.Controls 2.5

LoadListItem {
    property alias editText: itemNameEdit.text
    signal editAccepted
    signal editCanceled

    mainItem: TextField {
        id: itemNameEdit
        onAccepted: editAccepted()
        Keys.onEscapePressed: editCanceled()
    }

    function setEditFocus()
    {
        itemNameEdit.focus = true
    }
}
