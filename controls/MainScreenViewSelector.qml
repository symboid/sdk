
import QtQuick 2.12
import QtQuick.Controls 2.5

Row {
    property var viewNames: []
    property int currentIndex: 0
    readonly property int minWidth: prevButton.width + viewName.width + nextButton.width

    RoundButton {
        id: prevButton
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "/icons/br_prev_icon&24.png"
        enabled: currentIndex > 0
        onClicked: currentIndex--
    }
    HorizontalLine {
        anchors.verticalCenter: parent.verticalCenter
        width: (parent.width - minWidth) / 2
    }
    Label {
        id: viewName
        anchors.verticalCenter: parent.verticalCenter
        text: viewNames[currentIndex]
    }
    HorizontalLine {
        anchors.verticalCenter: parent.verticalCenter
        width: (parent.width - minWidth) / 2
    }
    RoundButton {
        id: nextButton
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "/icons/br_next_icon&24.png"
        enabled: currentIndex < (viewNames.length - 1)
        onClicked: currentIndex++
    }
}
