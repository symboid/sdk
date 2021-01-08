
import QtQuick 2.5
import QtQuick.Controls 2.12

SettingsItem {
    property alias title: titleLabel.text
    property alias text: valueLabel.text

    setting: Item {
        height: width < titleLabel.width + valueLabel.width ?
                    titleLabel.height + valueLabel.height + metricsPane.padding : titleLabel.height
        Pane {
            id: metricsPane
            visible: false
        }
        Label {
            id: titleLabel
        }
        Label {
            id: valueLabel
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            font.bold: true
        }
    }
}
