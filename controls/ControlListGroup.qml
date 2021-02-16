
import QtQuick 2.12
import QtQuick.Controls 2.5

ControlListItem {
    property alias title: titleLabel.text
    property alias titleAlignment: titleLabel.horizontalAlignment

    setting: Label {
        id: titleLabel
    }
}
