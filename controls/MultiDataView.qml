
import QtQuick 2.12
import QtQuick.Controls 2.5

IndirectContainer {
    property bool vertical: true
    container: swipeView
    reparentFrom: 3
    attachChild: function(newChild) { swipeView.addItem(newChild) }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        orientation: vertical ? Qt.Vertical : Qt.Horizontal
        interactive: false
        clip: true
    }

    Pane {
        anchors.top: parent.top
        anchors.left: parent.left
        background: null
        contentItem: RoundButton {
            background.opacity: 0.75
            icon.source: vertical ? "/icons/br_up_icon&24.png" : "/icons/br_prev_icon&24.png"
            visible: swipeView.currentIndex > 0
            onClicked: swipeView.currentIndex--
        }
    }

    Pane {
        anchors.bottom: vertical ? parent.bottom : undefined
        anchors.left: vertical ? parent.left : undefined
        anchors.top: vertical ? undefined : parent.top
        anchors.right: vertical ? undefined : parent.right
        background: null
        contentItem: RoundButton {
            icon.source: vertical ? "/icons/br_down_icon&24.png" : "/icons/br_next_icon&24.png"
            visible: swipeView.currentIndex < swipeView.count - 1
            onClicked: swipeView.currentIndex++
        }
    }
}
