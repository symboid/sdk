
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0
import Symboid.Sdk.Controls 1.0

ProcessPage {

    readonly property int rowWidth: 400

    Component {
        id: docComponent
        Document {
        }
    }
    property var loadDocument: function(documentPath, documentTitle)
    {
        return docComponent.createObject(this, { filePath: documentPath, title: documentTitle })
    }

    signal documentLoaded

    header: LoadListToolBar {
        listView: documentListView
        toolModel: ListModel {
            ListElement {
                iconSource: "/icons/doc_new_icon&32.png"
                withTextInput: true
                toolAction: function() {}
            }
            ListElement {
                iconSource: "/icons/trash_icon&32.png"
                toolAction: function() {
                    removeConfirm.open()
                }
            }
            ListElement {
                iconSource: "/icons/zoom_icon&32.png"
                withTextInput: true
                toolAction: function() {}
            }
        }
        onTextInputClicked: {
            if (textInputIndex === 0) {
                if (textInput !== 0) {
                    // loading the current document content as new content
                    loadDocument("",textInput)
                    documentLoaded()

                    textInputShow(false)
                }
            }
        }
        MessageDialog {
            id: removeConfirm
            message: qsTr("Do you want to remove the selected documents?")
            standardButtons: DialogButtonBox.Yes | DialogButtonBox.No
            onAccepted: {
                documentFolderModel.removeSelectedDocuments()
                documentListView.currentIndex = -1
            }
        }

    }

    DocumentFolderModel {
        id: documentFolderModel
    }

    function refresh()
    {
        documentFolderModel.updateDocumentList()
    }

    LoadListView {
        id: documentListView
        anchors.fill: parent
        model: documentFolderModel

        currentIndex: -1

        delegate: LoadListCheckItem {
            anchors.left: parent !== null ? parent.left : undefined
            anchors.right: parent !== null ? parent.right : undefined
            title: documentTitle
            cellWidth: Math.min(400, documentListView.width)
            selectable: index === documentListView.currentIndex
            onButtonClicked: {
                // loading selected document
                loadDocument(documentPath,"")
                documentLoaded()

                documentListView.currentIndex = -1
            }
            onSelectedChanged: documentSelected = selected
            selected: documentSelected
        }
    }
}
