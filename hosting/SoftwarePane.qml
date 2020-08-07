
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

SettingsPane {
    title: qsTr("Software")
    readonly property SoftwareVersion appVersion: SoftwareUpdate.appVersion
    readonly property SoftwareVersion astroVersion: SoftwareUpdate.astroVersion
    readonly property SoftwareVersion sdkVersion: SoftwareUpdate.sdkVersion
    SettingsGroup {
        title: qsTr("About")
        Rectangle {
            width: parent.width
            height: 100
            border.color: "blue"
        }
    }
    SettingsGroup {
        title: qsTr("Version details")
        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3
            rowSpacing: 10
            columnSpacing: 10
            Text {
                text: qsTr("Component")
                font.bold: true
            }
            Text {
                text: qsTr("Version")
                font.bold: true
            }
            Text {
                text: qsTr("Revision ID")
                font.bold: true
            }

            Text {
                text: qsTr("Application")
            }
            Text {
                text: "%1.%2.%3.%4".arg(appVersion.major).arg(appVersion.minor).arg(appVersion.patch).arg(appVersion.serial)
            }
            TextInput {
                text: appVersion.revid
                readOnly: true
                selectByMouse: true
            }

            Text {
                text: qsTr("Astro")
            }
            Text {
                text: "%1.%2.%3.%4".arg(astroVersion.major).arg(astroVersion.minor).arg(astroVersion.patch).arg(astroVersion.serial)
            }
            TextInput {
                text: astroVersion.revid
                readOnly: true
                selectByMouse: true
            }

            Text {
                text: qsTr("SDK")
            }
            Text {
                text: "%1.%2.%3.%4".arg(sdkVersion.major).arg(sdkVersion.minor).arg(sdkVersion.patch).arg(sdkVersion.serial)
            }
            TextInput {
                text: sdkVersion.revid
                readOnly: true
                selectByMouse: true
            }

        }
    }
    SettingsGroup {
        title: qsTr("Geographic database")
    }
    function setUpdateMethod()
    {
        SoftwareConfig.updateMethod =
                automatedSwUpdate.checked ? SoftwareConfig.UpdateAutomatic :
                   manualSwUpdate.checked ? SoftwareConfig.UpdateManual :
                                            SoftwareConfig.UpdateNone
    }
    SettingsGroup {
        id: swUpdateGroup
        title: qsTr("Update method")
        Grid {
            columns: 2
            rowSpacing: 10
            columnSpacing: 10
            verticalItemAlignment: Grid.AlignVCenter
            readonly property int textWidth: parent.width - automatedSwUpdate.width - columnSpacing
            RadioButton {
                id: automatedSwUpdate
                text: qsTr("Automated")
                font.bold: true
                checked: SoftwareConfig.updateMethod === SoftwareConfig.UpdateAutomatic
                onCheckedChanged: setUpdateMethod()
            }
            Text {
                width: parent.textWidth
                text: qsTr("Download and integration of new software revision will be performed automatically. New features will be available after application relaunch.")
                wrapMode: Text.WordWrap
            }
            RadioButton {
                id: manualSwUpdate
                text: qsTr("Manual")
                font.bold: true
                checked: SoftwareConfig.updateMethod === SoftwareConfig.UpdateManual
                onCheckedChanged: setUpdateMethod()
            }
            Text {
                width: parent.textWidth
                text: qsTr("Software updates will be prompted and confirmed. New features and bugfixes are available after update process.")
                wrapMode: Text.WordWrap
            }
            RadioButton {
                id: swUpdateOff
                text: qsTr("Switched off")
                font.bold: true
                checked: SoftwareConfig.updateMethod === SoftwareConfig.UpdateNone
                onCheckedChanged: setUpdateMethod()
            }
            Text {
                width: parent.textWidth
                text: qsTr("No software updates will be executed at all. No new features and bugfixes are available.")
                wrapMode: Text.WordWrap
            }
        }
    }
    SettingsGroup {
        title: qsTr("Update process")
    }
}
