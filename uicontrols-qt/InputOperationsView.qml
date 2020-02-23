
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.3
import Symboid.Sdk.Controls 1.0

InputOperations {

    property bool leftAligned: true

    Flickable {
        anchors.fill: parent

        flickableDirection: Flickable.VerticalFlick
        contentHeight: itemOperations.height
        Column {
            id: itemOperations
            anchors.left: parent.left
            anchors.right: parent.right
            Repeater {
                anchors.fill: parent
                model: operationCount
                delegate: Column {
                    readonly property InputOperation operation: operations[index]
                    property bool collapsed: true
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Pane {
                        anchors.left: parent.left
                        anchors.right: parent.right

                        Grid {
                            columns: 2
                            LayoutMirroring.enabled: !leftAligned
                            verticalItemAlignment: Grid.AlignVCenter
                            Row {
                                id: header
                                width: parent.parent.width - execButton.width
                                RoundButton {
                                    id: foldButton
                                    anchors.verticalCenter: parent.verticalCenter
                                    height: 32
                                    width: 32

                                    icon.source: collapsed ? "/icons/br_next_icon&24.png" : "/icons/br_down_icon&24.png"

                                    enabled: operation.control !== null
                                    onClicked: collapsed = !collapsed
                                }
                                Label {
                                    id: operationTitle
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: operation.title + ":"
                                    font.bold: true
                                    font.italic: true
                                }
                            }
                            RoundButton {
                                id: execButton
                                icon {
                                    source: leftAligned ? "/icons/arrow_right_icon&24.png"
                                                        : "/icons/arrow_left_icon&24.png"
                                }
                                enabled: operation.canExec
                                onClicked: operation.execute()
                            }
                            Loader {
                                id: operationPane
                                width: header.width
                                sourceComponent: operation.control
                                active: operation.control !== null
                                visible: !collapsed
                            }
                            Column {
                                width: execButton.width
                                height: operationPane.height
                                visible: !collapsed
                            }
                        }
                    }
                    Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 1
                        color: "black"
                    }
                }
            }
        }
    }
}
