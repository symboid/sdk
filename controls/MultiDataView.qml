
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12

Item {
    property bool vertical: true

    property ObjectModel dataViewModel: ObjectModel {
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        orientation: vertical ? Qt.Vertical : Qt.Horizontal
        interactive: false
        clip: true
        Repeater {
            model: dataViewModel
        }
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
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        background: null
        visible: vertical
        contentItem: RoundButton {
            icon.source: "/icons/br_down_icon&24.png"
            visible: swipeView.currentIndex < swipeView.count - 1
            onClicked: swipeView.currentIndex++
        }
    }

    Pane {
        anchors.top: parent.top
        anchors.right: parent.right
        background: null
        visible: !vertical
        contentItem: RoundButton {
            icon.source: "/icons/br_next_icon&24.png"
            visible: swipeView.currentIndex < swipeView.count - 1
            onClicked: swipeView.currentIndex++
        }
    }
}
