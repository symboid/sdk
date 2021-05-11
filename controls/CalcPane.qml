
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {

    property real progressPos: 0.0
    property bool calculating: false
    property bool autocalc: false
    property bool contentValid: false
    property bool indeterminateCalc: true
    property alias parameters: parametersSlot.contentItem

    signal startCalc()
    signal abortCalc()

    container: resultItem
    reparentFrom: 6

    ItemSlot {
        id: parametersSlot
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Item {
        id: resultItem
        anchors.top: parametersSlot.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        opacity: contentValid ? 1.0 : 0.5
    }

    Label {
        anchors.centerIn: parent
        visible: !contentValid
        text: calculating ? qsTr("Recalculating...") : qsTr("Data might be invalid!")
        horizontalAlignment: Label.AlignHCenter
        font.italic: true
        color: calculating ? "black" : "red"
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: calculating && indeterminateCalc
    }

    ProgressBar {
        id: calcProgress
        visible: calculating && !indeterminateCalc
        anchors.left: parent.left
        anchors.right: buttonPane.left
        anchors.verticalCenter: buttonPane.verticalCenter
        value: progressPos
    }

    Pane {
        id: buttonPane
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        background: null
        contentItem: RoundButton {
            radius: 5
            background.opacity: calculating ? 1 : 0.75
            icon.source: calculating ? "/icons/delete_icon&24.png" : "/icons/refresh_icon&24.png"
            highlighted: autocalc && !calculating
            onClicked: calculating ? abortCalc() : startCalc()
            onPressAndHold: autocalc = !autocalc
        }
    }
}
