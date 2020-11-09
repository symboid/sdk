
import QtQuick 2.12
import QtQuick.Controls 2.5

SettingsGroupExpanding {

    title: qsTr("User interface look and feel")

    SettingsItem {
        setting: ComboBox {
            model: [ "Material", "Universal", "Fusion", "Default" ]
        }
    }
}
