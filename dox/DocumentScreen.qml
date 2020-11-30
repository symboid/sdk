
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0
import Symboid.Sdk.Controls 1.0
import QtQuick.Layouts 1.12

Page {

    readonly property int rowWidth: 400

    property Document currentDocument: null
    signal documentLoaded

    header: LoadListToolBar {
        listView: documentListView
        toolModel: ListModel {
            ListElement {
                iconSource: "/icons/doc_new_icon&32.png"
                withTextInput: true
            }
            ListElement {
                iconSource: "/icons/trash_icon&32.png"
            }
            ListElement {
                iconSource: "/icons/zoom_icon&32.png"
                withTextInput: true
            }
        }
        onTextInputClicked: {
            if (textInputIndex === 0) {
                if (textInput !== 0) {
                    // loading the current document content as new content
                    currentDocument.loadCurrent()
                    currentDocument.title = textInput
                    documentLoaded()

                    textInputClose()
                }
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

        delegate: LoadListItem {
            anchors.left: parent.left
            anchors.right: parent.right
            itemTitle: documentTitle
            itemWidth: Math.min(rowWidth, documentListView.width)
            editable: index === documentListView.currentIndex
            selectable: index === documentListView.currentIndex
            onItemClicked: documentListView.currentIndex = index
            onButtonClicked: {
                // loading selected document
                currentDocument.filePath = documentPath
                currentDocument.load()
                documentLoaded()

                documentListView.currentIndex = -1
            }
        }
    }
}
