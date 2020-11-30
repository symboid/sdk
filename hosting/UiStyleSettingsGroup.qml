
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Hosting 1.0

SettingsItem {
    id: settingsItem
    setting: Row {
        spacing: 20
        Label {
            id: label
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("UI style:")
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
