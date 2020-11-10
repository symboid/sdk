
import QtQuick 2.12
import QtQuick.Controls 2.5

SettingsTreeNode {

    property alias title: titleLabel.text

    SettingsItem {
        setting: Label {
            id: titleLabel
        }
        rightItem: RoundButton {
            id: expandButton
            icon.source: "/icons/br_next_icon&24.png"
            onClicked: {
                if (settingsPane !== null) {
                    settingsView.addItem(settingsPane.createObject(null,{}))
                    settingsView.incrementCurrentIndex()
                }
            }
        }
    }

    property Component settingsPane: null
}
