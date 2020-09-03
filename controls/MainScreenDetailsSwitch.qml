
import QtQuick 2.12
import QtQuick.Controls 2.5

MainScreenBottomPane {
    property alias checked: detailsSwitch.checked
    width: metrics.isLandscape ? metrics.paramSectionWidth : metrics.screenWidth
    controlItem: Pane {
        Switch {
            id: detailsSwitch
            padding: 0
            anchors.centerIn: parent
            text: qsTr("Details")
        }
    }
}
