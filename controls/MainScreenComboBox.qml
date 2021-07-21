
import QtQuick 2.12
import QtQuick.Controls 2.5

MainScreenParamBox {
    property alias model: comboBox.model
    property alias textRole: comboBox.textRole
    property alias valueRole: comboBox.valueRole
    property alias currentIndex: comboBox.currentIndex
    property alias currentText: comboBox.currentText
    property alias currentValue: comboBox.currentValue

    Pane {
        width: metrics.paramSectionWidth - padding - leftPadding - rightPadding

        ComboBox {
            id: comboBox
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
