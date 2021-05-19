
import QtQuick 2.12
import QtQuick.Controls 2.5

IndirectContainer {
    container: swipeView
    reparentFrom: 3
    attachChild: function(newChild) { swipeView.addItem(newChild) }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        orientation: Qt.Vertical
        interactive: false
        clip: true
    }

    Pane {
        anchors.top: parent.top
        anchors.left: parent.left
        contentItem: RoundButton {
            background.opacity: 0.75
            icon.source: "/icons/br_up_icon&24.png"
            visible: swipeView.currentIndex > 0
            onClicked: swipeView.currentIndex--
        }
    }

    Pane {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        background: null
        contentItem: RoundButton {
            icon.source: "/icons/br_down_icon&24.png"
            visible: swipeView.currentIndex < swipeView.count - 1
            onClicked: swipeView.currentIndex++
        }
    }
}
