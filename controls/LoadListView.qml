
import QtQuick 2.12
import QtQuick.Controls 2.5

ListView {
    id: documentListView

    readonly property int rowWidth: 400

    clip: true
    highlightFollowsCurrentItem: true
    highlightMoveVelocity: -1
    highlightResizeDuration: 0
    highlightResizeVelocity: -1
    highlight: Item {
        Rectangle {
            anchors.left: parent.left
            anchors.right: middle.left
            height: middle.height
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 1.0; color: middle.color }
                GradientStop { position: 0.0; color: "white" }
            }
        }
        Rectangle {
            id: middle
            anchors.centerIn: parent
            height: parent.height
            width: rowWidth
            color: "lightgray"
        }
        Rectangle {
            anchors.left: middle.right
            anchors.right: parent.right
            height: middle.height
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: middle.color }
                GradientStop { position: 1.0; color: "white" }
            }
        }
    }
}
