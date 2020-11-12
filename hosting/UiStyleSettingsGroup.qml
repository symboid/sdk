
import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.settings 1.0

SettingsGroupExpanding {

    title: qsTr("User interface look and feel")

    Settings {
        id: appSettings
        category: "ui"
        property string style: ""
    }

    SettingsItem {
        id: settingsItem
        setting: Row {
            spacing: 50
            Label {
                id: label
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Style:")
            }
            ComboBox {
                width: 200
                Component.onCompleted: {
                    var style = appSettings.style
                    var styleIndex = -1
                    for (var i = 0; styleIndex === -1 && i < count; ++i)
                    {
                        if (model[i] === style) {
                            styleIndex = i
                        }
                    }
                    currentIndex = styleIndex
                }
                model: [ "Material", "Universal", "Fusion", "Default" ]
                onCurrentTextChanged: {
                    appSettings.style = currentText
                }
            }
        }
        hint: qsTr("In order to apply the selected UI style the application must be restarted!")
    }
}
