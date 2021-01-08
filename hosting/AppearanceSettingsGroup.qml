
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
                wrapMode: Label.WordWrap
                font.italic: true
            }
            rightItem: Button {
                text: qsTr("Restart")
                highlighted: true
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
        SettingsSwitch {
            text: qsTr("Dark theme")
        }

        SettingsGroupFixed {
            title: qsTr("UI control sizes")
        }
        ButtonGroup {
            buttons: [ devicePixelSetting.button, logicalPixelSetting.button ]
        }
        SettingsRadioButton {
            id: devicePixelSetting
            text: qsTr("Follows device pixel size (usually smaller)")
        }
        SettingsRadioButton {
            id: logicalPixelSetting
            text: qsTr("Follows desktop's logical pixel size (usually bigger)")
        }

        SettingsGroupFixed {
            title: qsTr("Graphical acceleration")
        }
        SettingsCheckBox {
            enabled: false
            text: qsTr("Using Open GL software infrastructure")
            hint: qsTr("Recommended on old systems (e.g. Windows 7)")
        }

    }
}
