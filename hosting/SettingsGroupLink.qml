
import QtQuick 2.12
import QtQuick.Controls 2.5

SettingsGroup {

    rightItem: RoundButton {
        id: expandButton
        icon.source: "/icons/br_next_icon&24.png"
        onClicked: {
            if (settingsPane !== null) {
                settingsView.push(settingsPane.createObject(settingsView,{}))
            }
        }
    }

    property Component settingsPane: null
}
