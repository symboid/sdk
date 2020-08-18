
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

Pane {
    id: boxPane
    property alias selectedDocumentPath: documentFolderView.selectedPath
    property alias documentTitle: titleField.text
    property alias documentIndex: documentFolderView.currentIndex
    property bool titleFiltering: false

    signal documentDeleted(string documentPath)

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
            onDocumentSelected: {
                if (!titleFiltering)
                {
                    titleField.text = selectedTitle
                }
            }
            onDocumentDeleted: boxPane.documentDeleted(documentPath)
        }
    }
    function updateModel()
    {
        documentFolderView.updateModel()
    }
}
