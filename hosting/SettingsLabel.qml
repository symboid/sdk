
import QtQuick 2.5
import QtQuick.Controls 2.12

SettingsItem {
    property alias title: titleLabel.text
    property alias text: valueLabel.text

    setting: Flow {
        id: labelFlow
        readonly property bool wrapped: width < titleLabel.width + valueLabel.width + 2*metricsPane.padding
        readonly property Item metricsPane: Pane {
        }
        Label {
            id: titleLabel
        }
        Item {
            width: labelFlow.wrapped ? cellWidth - titleLabel.width : 0
            height: 1
        }
        Item {
            width: labelFlow.wrapped ? cellWidth - valueLabel.width : cellWidth - (titleLabel.width + valueLabel.width)
            height: 1
        }
        Label {
            id: valueLabel
            font.bold: true
        }
    }
}
