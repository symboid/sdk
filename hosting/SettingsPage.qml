
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0

ProcessPage {

    header: ToolBar {
        id: toolbar
        ToolButton {
            icon.source: "/icons/br_prev_icon&32.png"
            enabled: settingsView.depth > 1
            onClicked: settingsView.pop()
        }
        Label {
            anchors.centerIn: parent
            text: settingsView.currentItem.title
            font.italic: true
        }
    }

    property SettingsView settingsView: sv

    contentItem: SettingsView {
        id: sv
        anchors.fill: parent
        initialItem: SettingsPane {
            id: firstPane
            title: qsTr("Settings")
        }
        contentItem: firstPane
    }
}
