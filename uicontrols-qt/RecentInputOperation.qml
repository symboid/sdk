
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0

InputOperation {

    property alias itemModel: recentItems.model
    property Component itemComponent: Label {
        text: inputItemTitle
    }

    signal itemSelected(int itemIndex)

    control: Pane {
        id: listViewWrapper
        height: 500
        ListView {
            id: recentItems
            anchors.fill: parent
            delegate: Pane {
                Loader {
                    readonly property string inputItemTitle: itemTitle
                    readonly property int itemSpace: parent.width
                    sourceComponent: itemComponent
                }
                width: parent.width
                background: Rectangle {
                    border {
                        width: 1
                        color: index == recentItems.currentIndex ? "lightgray" : "transparent"
                    }
                    radius: 5
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            recentItems.currentIndex = index
                            itemSelected(index)
                        }
                    }
                }
            }
        }
    }
    canExec: recentItems.currentIndex != -1
}
