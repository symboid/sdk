
import QtQuick 2.12
import QtQuick.Controls 2.5

Frame {
    property bool showFrame: false
    topInset: 0
    leftInset: 0
    rightInset: 0
    bottomInset: 0
    topPadding: 0
    leftPadding: 0
    rightPadding: 0
    bottomPadding: 0
    Component.onCompleted: {
        if (showFrame )
        {
            background.border.color = "red"
        }
        else
        {
            background = null
        }
    }
}
