
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
/*
            id: versionDetails
            property int col1Width: 100
            property int col2Width: 100
            Row {
                Text {
                    text: qsTr("Component")
                    font.bold: true
                    width: versionDetails.col1Width
                }
                Text {
                    text: qsTr("Version")
                    font.bold: true
                    width: versionDetails.col2Width
                }
                Text {
                    text: qsTr("Revision ID")
                    font.bold: true
                }
            }
            ListView {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 150
                clip: true
                model: SoftwareUpdate.componentVersions
                delegate: Row {
                    anchors.topMargin: 10
                    Text {
                        text: name
                        width: versionDetails.col1Width
                    }
                    Text {
                        text: "%1.%2.%3.%4".arg(major).arg(minor).arg(patch).arg(serial)
                        width: versionDetails.col2Width
                    }
                    TextInput {
                        text: revid
                        readOnly: true
                        selectByMouse: true
                    }
                }
            }
            */
        }
    }
    SettingsGroupExpanding {
        title: qsTr("Geographic database")
    }

    function setUpdateMethod()
    {
        SoftwareConfig.updateMethod =
                automatedSwUpdate.checked ? SoftwareConfig.UpdateAutomatic :
                   manualSwUpdate.checked ? SoftwareConfig.UpdateManual :
                                            SoftwareConfig.UpdateNone
    }
    SettingsGroupExpanding {
        id: swUpdateGroup
        title: qsTr("Update")
        ButtonGroup {
            id: updateMethonGroup
            buttons: [ automatedSwUpdate, manualSwUpdate, swUpdateOff]
        }

        SettingsItem {
            setting: RadioButton {
                id: automatedSwUpdate
                text: qsTr("Automated")
                font.bold: true
                checked: SoftwareConfig.updateMethod === SoftwareConfig.UpdateAutomatic
                onCheckedChanged: setUpdateMethod()
            }
            hint: qsTr("Download and integration of new software revision will be performed automatically. New features will be available after application relaunch.")
        }

        SettingsItem {
            setting: RadioButton {
                id: manualSwUpdate
                text: qsTr("Manual")
                font.bold: true
                checked: SoftwareConfig.updateMethod === SoftwareConfig.UpdateManual
                onCheckedChanged: setUpdateMethod()
            }
            hint: qsTr("Software updates will be prompted and confirmed. New features and bugfixes are available after update process.")
        }
        SettingsItem {
            setting: RadioButton {
                id: swUpdateOff
                text: qsTr("Switched off")
                font.bold: true
                checked: SoftwareConfig.updateMethod === SoftwareConfig.UpdateNone
                onCheckedChanged: setUpdateMethod()
            }
            hint: qsTr("No software updates will be executed at all. No new features and bugfixes are available.")
        }
    }
}
