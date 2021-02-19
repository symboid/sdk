
import QtQuick 2.12
import QtQuick.Controls 2.5

ControlListGroup {

    rightItem: RoundButton {
        id: expandButton
        icon.source: "/icons/br_next_icon&24.png"
        onClicked: controlListView.loadPane(controlListPane)
    }

    property Component controlListPane: null
}
