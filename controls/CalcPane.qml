
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {

    property alias calcable: task.calcable
    readonly property bool calculating: task.running
    property bool indeterminateCalc: true
    property alias parameters: parametersSlot.contentItem
    property bool autocalc: task.autorun
    onAutocalcChanged: task.autorun = autocalc
    property bool buttonVisible: true

    container: resultItem
    reparentFrom: 5

    signal calcTaskStarted
    signal calcTaskFinished
    signal calcTaskAborted

    CalcTask {
        id: task
        onStarted: calcTaskStarted()
        onFinished: calcTaskFinished()
        onAborted: calcTaskAborted()
    }

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
        opacity: task.valid ? 1.0 : 0.5
    }

    Column {
        anchors.centerIn: parent
        BusyIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            running: calculating && indeterminateCalc
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: !task.valid
            text: calculating ? qsTr("Recalculating...") : qsTr("Data might be invalid!")
            horizontalAlignment: Label.AlignHCenter
            font.italic: true
            color: calculating ? "black" : "red"
        }
    }

    ProgressBar {
        id: calcProgress
        visible: calculating && !indeterminateCalc
        anchors.left: parent.left
        anchors.right: buttonPane.left
        anchors.verticalCenter: buttonPane.verticalCenter
        value: task.progress
    }

    Pane {
        id: buttonPane
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        background: null
        visible: buttonVisible || calculating
        contentItem: RoundButton {
            radius: 5
            background.opacity: calculating ? 1 : 0.75
            icon.source: calculating ? "/icons/delete_icon&24.png" : "/icons/refresh_icon&24.png"
            highlighted: autocalc && !calculating
            onClicked: calculating ? task.abort() : task.start()
            onPressAndHold: autocalc = !autocalc
        }
    }
}
