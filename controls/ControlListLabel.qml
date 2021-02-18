
import QtQuick 2.5
import QtQuick.Controls 2.12

ControlListItem {
    property alias title: titleLabel.text
    property alias text: valueLabel.text

    mainItem: Flow {
        id: labelFlow
        readonly property bool wrapped: width < titleLabel.width + valueLabel.width + spacing
        readonly property Item metricsPane: Pane {
        }
        spacing: metricsPane.padding
        Label {
            id: titleLabel
        }
        Item {
            width: labelFlow.wrapped ? cellWidth - titleLabel.width - labelFlow.spacing : 0
            height: 1
        }
        Item {
            width: labelFlow.wrapped ? cellWidth - valueLabel.width - labelFlow.spacing : cellWidth - (titleLabel.width + valueLabel.width + 2*labelFlow.spacing)
            height: 1
        }
        Label {
            id: valueLabel
            font.bold: true
        }
    }
}
