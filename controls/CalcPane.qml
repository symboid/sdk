
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Item {

    default property alias items: resultItem.children

    property alias calcable: task.calcable
    readonly property bool calculating: task.running
    property bool indeterminateCalc: true
    property bool autocalc: task.autorun
    onAutocalcChanged: task.autorun = autocalc
    property bool showButton: true
    property alias buttonVisible: buttonPane.visible
    readonly property alias buttonSize: button.width

    signal calcTaskStarted
    signal calcTaskFinished
    signal calcTaskAborted

    CalcTask {
        id: task
        onStarted: calcTaskStarted()
        onFinished: calcTaskFinished()
        onAborted: calcTaskAborted()
    }

    Item {
        id: resultItem
        anchors.fill: parent
        opacity: task.valid ? 1.0 : 0.5
    }

    Column {
        anchors.centerIn: parent
        z: 100
        BusyIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: running
            running: calculating && indeterminateCalc
        }
        Button {
            background: null
            anchors.horizontalCenter: parent.horizontalCenter
            visible: !task.valid && !calculating
            icon.source: "/icons/attention_icon&48.png"
            icon.color: "#C94848"
            icon.width: 48
            icon.height: 48
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
        visible: showButton || calculating
        contentItem: RoundButton {
            id: button
            radius: 5
            background.opacity: calculating ? 1 : 0.75
            icon.source: calculating ? "/icons/delete_icon&24.png" : "/icons/refresh_icon&24.png"
            highlighted: autocalc && !calculating
            onClicked: calculating ? task.abort() : task.start()
            onPressAndHold: autocalc = !autocalc
        }
    }
}
