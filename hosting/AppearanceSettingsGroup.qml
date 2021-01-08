
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

SettingsGroupLink {

    title: qsTr("Appearance")
    settingsPane: SettingsPane {
        title: qsTr("Appearance")
        SettingsItem {
            setting: Label {
                text: qsTr("Every single change on this pane can only take effect after application restart.")
                height: contentHeight
                wrapMode: Label.WordWrap
                font.italic: true
            }
            rightItem: Button {
                text: qsTr("Restart")
                highlighted: true
                onClicked: AppConfig.restartApp()
            }
        }

        SettingsGroupFixed {
            title: qsTr("Look and feel settings")
        }
        SettingsItem {
            setting: Row {
                spacing: 20
                Label {
                    id: label
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Style:")
                }
                ComboBox {
                    currentIndex: AppConfig.ui.styleIndex
                    model: AppConfig.ui.styleModel
                    onCurrentIndexChanged: {
                        AppConfig.ui.style = model[currentIndex]
                    }
                }
            }
            hint: qsTr("In order to apply the selected UI style the application must be restarted!")
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
