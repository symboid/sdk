
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Hosting 1.0

SettingsGroupExpanding {

    title: qsTr("User interface look and feel")

    SettingsItem {
        id: settingsItem
        setting: Row {
            spacing: 10
            Label {
                id: label
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Style:")
            }
            ComboBox {
//                width: 200
                currentIndex: {
                    var style = AppConfig.ui.style
                    var styleIndex = -1
                    for (var i = 0; styleIndex === -1 && i < count; ++i)
                    {
                        if (model[i] === style) {
                            styleIndex = i
                        }
                    }
                    return styleIndex
                }
                model: [ "Default", "Material", "Universal", "Fusion" ]
                onCurrentIndexChanged: {
                    AppConfig.ui.style = model[currentIndex]
                }
            }
        }
        hint: qsTr("In order to apply the selected UI style the application must be restarted!")
    }
}
