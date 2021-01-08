
import QtQuick 2.5
import QtQuick.Controls 2.12

SettingsItem {
    property alias title: titleLabel.text
    property alias text: valueLabel.text

    setting: Item {
        height: width < titleLabel.width + valueLabel.width + 2*metricsPane.padding ?
                    titleLabel.height + valueLabel.height + metricsPane.padding : titleLabel.height
        readonly property Item metricsPane: Pane {
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
