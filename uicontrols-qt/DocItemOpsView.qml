
import QtQuick 2.12
import QtQuick.Controls 2.12

Flickable {

    property bool leftAligned: true

    property Container operations: null
    readonly property int operationCount: operations !== null ? operations.contentChildren.length : 0

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
                anchors.left: parent.left
                anchors.right: parent.right
                readonly property DocItemOp operation: operations.contentChildren[index]
                readonly property int space: 10
                Item {
                    height: 32 + 2*parent.space
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Row {
                        height: parent.height
                        padding: parent.parent.space
                        Loader {
                            height: parent.height
                            width: height
                            anchors.verticalCenter: parent.verticalCenter
                            sourceComponent: loadButtonComponent
                            active: !leftAligned
                            visible: !leftAligned
                        }
                        RoundButton {
                            id: foldButton
                            anchors.verticalCenter: parent.verticalCenter
                            height: 32
                            width: 32

                            icon.source: "/icons/br_down_icon&24.png"
                            icon.height: 24
                            icon.width: 24
                        }
                        Label {
                            id: operationTitle
                            anchors.verticalCenter: parent.verticalCenter
                            text: operation.title + ":"
                            font.bold: true
                            font.italic: true
                        }
                    }
                    Loader {
                        sourceComponent: loadButtonComponent
                        active: leftAligned
                        anchors.right: parent.right
                        anchors.rightMargin: parent.space
                        height: parent.height
                        width: height
                    }
                    Component {
                        id: loadButtonComponent
                        RoundButton {
                            icon {
                                source: leftAligned ? "/icons/arrow_right_icon&24.png"
                                                    : "/icons/arrow_left_icon&24.png"
                                width: 24
                                height: 24
                                color: "darkblue"
                            }
                        }
                    }
                }

                Loader {
                    id: operationLoader
                    anchors.margins: parent.space
                    anchors.left: parent.left
                    anchors.right: parent.right
                    sourceComponent: operation.control
                    active: operation.control !== null
                }
                Item {
                    height: parent.space
                    width: operation.control !== null ? 1 : 0
                }

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1
                    color: "black"
                    visible: index < operationCount - 1
                }
            }
        }
    }
}
