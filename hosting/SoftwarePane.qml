
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

SettingsPane {
    title: qsTr("Software")
    SettingsGroup {
        title: qsTr("About")
        Rectangle {
            width: parent.width
            height: 100
            border.color: "blue"
        }
    }
    SettingsGroup {
        title: qsTr("Version")
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
