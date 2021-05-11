
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Item {

    property real progressPos: 0.0
    property bool calculating: false
    property bool autocalc: false
    property bool contentValid: false
    property bool indeterminateCalc: true

    signal startCalc()
    signal abortCalc()

    BusyIndicator {
        z: parent.z + 1
        anchors.centerIn: parent
        running: calculating && indeterminateCalc
    }

    ProgressBar {
        id: calcProgress
        z: parent.z + 1
        visible: calculating && !indeterminateCalc
        anchors.left: parent.left
        anchors.right: buttonPane.left
        anchors.verticalCenter: buttonPane.verticalCenter
        value: progressPos
        opacity: 0.5
    }

    Pane {
        id: buttonPane
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        background: null
        z: parent.z + 1
        contentItem: RoundButton {
            radius: 5
            background.opacity: 0.5
            icon.source: calculating ? "/icons/delete_icon&24.png" : "/icons/refresh_icon&24.png"
            highlighted: autocalc && !calculating
            onClicked: calculating ? abortCalc() : startCalc()
            onPressAndHold: autocalc = !autocalc
        }
    }
}
