
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {

    container: firstPane
    reparentFrom: 2

    property string initialTitle: ""
    property bool withBackButton: false
    signal backButtonClicked

    ToolBar {
        id: toolbar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        ToolButton {
            icon.source: "/icons/br_prev_icon&32.png"
            enabled: controlListView.depth > 1 || withBackButton
            onClicked: {
                if (controlListView.depth > 1)
                {
                    controlListView.pop()
                }
                else if (withBackButton)
                {
                    backButtonClicked()
                }
            }
        }
        Label {
            anchors.centerIn: parent
            text: controlListView.currentItem.title
            font.italic: true
        }
    }

    property ControlListView controlListView: sv
    ControlListView {
        id: sv
        anchors {
            top: toolbar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        initialItem: ControlListPane {
            id: firstPane
            title: initialTitle
        }
    }
}
