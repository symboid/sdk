
import QtQuick 2.12
import QtQuick.Controls 2.5

MainScreenBottomPane {
    property var viewNames: []
    property int currentIndex: 0
    width: metrics.isLandscape ? metrics.paramSectionWidth : metrics.screenWidth

    controlItem: Item {
        height: prevButton.height
        RoundButton {
            id: prevButton
            anchors.left: parent.left
            icon.source: "/icons/br_prev_icon&24.png"
            enabled: currentIndex > 0
            onClicked: currentIndex--
        }
        Rectangle {
            anchors.left: prevButton.right
            anchors.right: viewName.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10
            height: 1
            color: "lightgrey"
        }
        Label {
            id: viewName
            anchors.centerIn: parent
            text: viewNames[currentIndex]
        }
        Rectangle {
            anchors.left: viewName.right
            anchors.right: nextButton.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10
            height: 1
            color: "lightgrey"
        }
        RoundButton {
            id: nextButton
            anchors.right: parent.right
            icon.source: "/icons/br_next_icon&24.png"
            enabled: currentIndex < (viewNames.length - 1)
            onClicked: currentIndex++
        }
    }
}
