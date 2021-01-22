
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Symboid.Sdk.Controls 1.0

IndirectContainer {

    container: firstPane
    reparentFrom: 2

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
            enabled: settingsView.depth > 1 || withBackButton
            onClicked: {
                if (settingsView.depth > 1)
                {
                    settingsView.pop()
                }
                else if (withBackButton)
                {
                    backButtonClicked()
                }
            }
        }
        Label {
            anchors.centerIn: parent
            text: settingsView.currentItem.title
            font.italic: true
        }
    }

    property SettingsView settingsView: sv
    SettingsView {
        id: sv
        anchors {
            top: toolbar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        initialItem: SettingsPane {
            id: firstPane
            title: qsTr("Settings")
        }
    }
}
