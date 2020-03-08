
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

Pane {
    id: boxPane
    readonly property alias selectedDocumentPath: documentFolderView.selectedPath
    property alias documentTitle: titleField.text
    property bool titleFiltering: false

    TextField {
        id: titleField
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        Image {
            id: titleIcon
            source: titleFiltering ? "/icons/zoom_icon&16.png" : "/icons/pencil_icon&16.png"
            anchors.left: parent.left
            anchors.leftMargin: parent.topPadding
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    titleFiltering = !titleFiltering
                }
            }
        }
        leftPadding: titleIcon.width + 2 * topPadding
    }

    Frame {
        anchors {
            top: titleField.bottom
            topMargin: boxPane.padding
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        DocumentFolderView {
            id: documentFolderView
            anchors.fill: parent
            filterText: titleFiltering ? titleField.text : ""
        }
    }
}
