
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

SettingsGroupLink {

    title: qsTr("Appearance")
    settingsPane: SettingsPane {
        title: qsTr("Appearance")
        SettingsItem {
            mainItem: Label {
                text: qsTr("Every single change on this pane can only take effect after application restart.")
                width: cellWidth - restartButton.width
                wrapMode: Label.WordWrap
                font.italic: true
            }
            rightItem: Button {
                id: restartButton
                text: qsTr("Restart")
                highlighted: true
                onClicked: AppConfig.restartApp()
            }
        }

        SettingsGroupFixed {
            title: qsTr("Look and feel settings")
        }
        SettingsItem {
                anchors.verticalCenter: parent.verticalCenter
            title: qsTr("Style")
            rightItem: ComboBox {
                currentIndex: AppConfig.ui.styleIndex
                model: AppConfig.ui.styleModel
                onCurrentIndexChanged: {
                    AppConfig.ui.style = model[currentIndex]
                }
            }
        }
        SettingsGroupFixed {
            title: qsTr("Graphical rendering")
        }
        SettingsCheckBox {
            text: qsTr("High DPI scaling")
            hint: qsTr("Control sizes calculated based on higher pixel density if available.")
            configNode: AppConfig.ui.high_dpi_scaling_node
        }
    }
}
