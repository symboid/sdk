
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0
import Symboid.Sdk.Network 1.0

SettingsGroupFixed {
    title: qsTr("Software")
    SettingsGroupExpanding {
        title: qsTr("About")
        SettingsGroupLink {
            title: qsTr("Build information")
            settingsPane: SettingsPane {
                title: qsTr("Build information")
                SettingsGroupFixed {
                    title: qsTr("Components")
                    Repeater {
                        model: SoftwareUpdate.componentVersions
                        SettingsItem {
                            setting: Column {
                                spacing: 10
                                Label {
                                    text: name
                                    font.bold: true
                                }
                                Label {
                                    text: '<a href="https://github.com/symboid/' + name + '">https://github.com/symboid/' + name + '</a>'
                                    anchors.right: parent.right
                                }
                                TextInput {
                                    anchors.right: parent.right
                                    text: revid
                                    readOnly: true
                                    selectByMouse: true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    SettingsGroupExpanding {
        title: qsTr("Geographic database")
    }
    SettingsGroupExpanding {
        title: qsTr("Update")
        ButtonGroup {
            buttons: [ automatedSwUpdate.button, manualSwUpdate.button, noSwUpdate.button ]
        }
        SettingsRadioButton {
            id: automatedSwUpdate
            text: qsTr("Automated")
//            enabled: false
            enumConfig: AppConfig.software.update_method_node
            enumValue: 0//SoftwareConfig.UpdateAutomatic
            hint: qsTr("Download and integration of new software revision will be performed automatically. New features will be available after application relaunch.")
        }
        SettingsRadioButton {
            id: manualSwUpdate
            text: qsTr("Manual")
            enumConfig: AppConfig.software.update_method_node
            enumValue: 1//SoftwareConfig.UpdateManual
            hint: qsTr("Software updates will be prompted and confirmed. New features and bugfixes are available after update process.")
        }
        SettingsRadioButton {
            id: noSwUpdate
            text: qsTr("Switched off")
            enumConfig: AppConfig.software.update_method_node
            enumValue: 2//SoftwareConfig.UpdateNone
            hint: qsTr("No software updates will be executed at all. No new features and bugfixes are available.")
        }
    }
}
