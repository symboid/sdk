
import QtQuick 2.12
import QtQuick.Controls 2.5

Frame {
    property color color: "lightgray"
    onColorChanged: background.border.color = color
    Component.onCompleted: {
        background.border.color = "lightgray"
        width = background.border.width
    }
}
