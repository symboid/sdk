
import QtQuick 2.12
import QtQuick.Controls 2.5

FolderItem {
    property alias loadIconSource: loadButton.icon.source
    readonly property alias loadButtonSpace: loadButtonPane.width
    signal buttonClicked

    rightItem: Pane {
        id: loadButtonPane
        background: null
        topPadding: 0
        bottomPadding: 0
        RoundButton {
            id: loadButton
            icon.source: revertedLayout ? "/icons/br_prev_icon&24.png" : "/icons/br_next_icon&24.png"
            visible: icon.source !== ""
            onClicked: buttonClicked()
        }
    }
}
