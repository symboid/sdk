
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

ListView {

    property alias filterText: documentFolderModel.filterText
    property string selectedPath: ""

    signal documentSelected(string selectedTitle)
    signal documentDeleted(string documentPath)

    clip: true
    DocumentFolderModel {
        id: documentFolderModel
        onFilterTextChanged: {
            selectedPath = ""
            currentIndex = -1
        }
        onDocumentRemoved: {
            documentDeleted(documentPath)
        }
    }
    function updateModel()
    {
        documentFolderModel.updateDocumentList()
    }

    model: documentFolderModel
    currentIndex: -1

    highlightFollowsCurrentItem: true
    highlightMoveVelocity: -1
    highlight: Rectangle {
        color: "lightgray"
        radius: 5
    }

    delegate: Pane {
        id: itemPane
        Label {
            id: titleLabel
            text: documentTitle
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    currentIndex = index
                    selectedPath = documentPath
                    documentSelected(documentTitle)
                }
            }
        }
        width: parent.width
        background: Item {
            RoundButton {
                z: titleLabel.z + 1
                anchors.right: parent.right
                anchors.rightMargin: (parent.height - height) / 2
                anchors.verticalCenter: parent.verticalCenter
                visible: index == currentIndex
                icon.source: "/icons/delete_icon&16.png"
                width: 32
                height: 32
                onClicked: {
                    var removeIndex = currentIndex
                    currentIndex = -1
                    var documentPath = documentFolderModel.data(documentFolderModel.index(removeIndex,0), DocumentFolderModel.DocumentPath)
                    if (documentFolderModel.removeDocument(removeIndex))
                    {
//                        context.onDocumentDeleted(documentPath)
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    currentIndex = index
                    selectedPath = documentPath
                    documentSelected(documentTitle)
                }
            }
        }
    }
}
