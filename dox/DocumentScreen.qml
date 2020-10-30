
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
                    // saving previously loaded document
                    currentDocument.save()

                    currentDocument.loadCurrent()
                    currentDocument.title = textInput
                    currentDocument.save()
                    documentLoaded()
                    documentFolderModel.updateDocumentList()

                    textInputClose()
                }
            }
        }
    }

    DocumentFolderModel {
        id: documentFolderModel
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
            itemWidth: rowWidth
            editable: index === documentListView.currentIndex
            selectable: index === documentListView.currentIndex
            onItemClicked: documentListView.currentIndex = index
            onButtonClicked: {
                // saving previously loaded document
                currentDocument.save()

                // loading selected document
                currentDocument.filePath = documentPath
                currentDocument.load()
                documentLoaded()

                documentListView.currentIndex = -1
            }
        }
    }
}
