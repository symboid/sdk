
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0
import Symboid.Sdk.Controls 1.0
import QtQuick.Layouts 1.12

Page {

    readonly property int rowWidth: 400

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
    }

    DocumentFolderModel {
        id: documentFolderModel
        /*
        onFilterTextChanged: {
            selectedPath = ""
            currentIndex = -1
        }
        onDocumentRemoved: {
            documentDeleted(documentPath)
        }
        */
    }

    LoadListView {
        id: documentListView
        anchors.fill: parent
        model: documentFolderModel

        delegate: LoadListItem {
            anchors.left: parent.left
            anchors.right: parent.right
            itemTitle: documentTitle
            itemWidth: rowWidth
            editable: documentListView === null || index === documentListView.currentIndex
            selectable: documentListView !== null && index === documentListView.currentIndex
            onItemClicked: documentListView.currentIndex = index
        }
    }
}
