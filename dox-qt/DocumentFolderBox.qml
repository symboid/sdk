
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

Pane {
    id: boxPane
    TextField {
        id: searchText
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        Image {
            id: searchIcon
            source: "/icons/zoom_icon&24.png"
            anchors.left: parent.left
            anchors.leftMargin: parent.topPadding
            anchors.verticalCenter: parent.verticalCenter
        }
        leftPadding: searchIcon.width + 2 * topPadding
    }

    Frame {
        anchors {
            top: searchText.bottom
            topMargin: boxPane.padding
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        DocumentFolderView {
            anchors.fill: parent
            filterText: searchText.text
        }
    }
}
