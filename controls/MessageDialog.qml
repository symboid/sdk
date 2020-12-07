
import QtQuick 2.12
import QtQuick.Controls 2.5

Dialog {
    width: parent.width
    contentItem: Column {
        Rectangle {
            width: 400
            height: 150
            border.color: "red"
            border.width: 1
        }
    }
    footer: DialogButtonBox {
        alignment: Qt.AlignHCenter
        standardButtons: DialogButtonBox.Yes | DialogButtonBox.No
    }

}
