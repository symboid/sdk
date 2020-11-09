
import QtQuick 2.12
import QtQuick.Controls 2.5

SettingsTreeNode {

    property alias title: titleLabel.text

    SettingsItem {
        background: Rectangle {
            color: "lightgray"
        }
        setting: Label {
            id: titleLabel
        }
    }
}
