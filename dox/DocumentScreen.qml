
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0
import Symboid.Sdk.Controls 1.0
import QtQuick.Layouts 1.12

Page {

    readonly property int rowWidth: 400

    header: ToolBar {
        id: toolbar
        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                ToolButton {
                    id: newButton
                    icon.source: "file:///home/robert/Munka/icons/black/png/doc_new_icon&32.png"
                    icon.height: height
                    icon.width: width
                    checkable: true
                    enabled: !filterButton.checked
                    onCheckedChanged: {
                        if (checked) {
                            documentListView.currentIndex = -1
                            filterItem.setEditFocus()
                        }
                    }
                }
                ToolButton {
                    icon.source: "file:///home/robert/Munka/icons/black/png/trash_icon&32.png"
                    icon.height: height
                    icon.width: width
                }
                ToolButton {
                    id: filterButton
                    icon.source: "file:///home/robert/Munka/icons/black/png/zoom_icon&32.png"
                    icon.height: height
                    icon.width: width
                    checkable: true
                    enabled: !newButton.checked
                    onCheckedChanged: {
                        if (checked) {
                            documentListView.currentIndex = -1
                            filterItem.setEditFocus()
                        }
                    }
                }
            }
            DocumentListItem {
                id: filterItem
                visible: filterButton.checked || newButton.checked
                anchors.horizontalCenter: parent.horizontalCenter
                width: toolbar.width
                itemWidth: rowWidth
                loadIconSource: newButton.checked ? "file:///home/robert/Munka/icons/black/png/doc_new_icon&32.png" : ""
                lineColor: toolbar.background.color
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

    ListView {
        id: documentListView
        anchors.fill: parent
        model: documentFolderModel

        clip: true
        highlightFollowsCurrentItem: true
        highlightMoveVelocity: -1
        highlightResizeDuration: 0
        highlightResizeVelocity: -1
        highlight: Item {
            Rectangle {
                anchors.left: parent.left
                anchors.right: middle.left
                height: middle.height
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 1.0; color: middle.color }
                    GradientStop { position: 0.0; color: "white" }
                }
            }
            Rectangle {
                id: middle
                anchors.centerIn: parent
                height: parent.height
                width: rowWidth
                color: "lightgray"
            }
            Rectangle {
                anchors.left: middle.right
                anchors.right: parent.right
                height: middle.height
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: middle.color }
                    GradientStop { position: 1.0; color: "white" }
                }
            }
        }
        delegate: DocumentListItem {
            anchors.left: parent.left
            anchors.right: parent.right
            itemTitle: documentTitle
            itemWidth: rowWidth
            loadIconSource: "file:///home/robert/Munka/icons/black/png/br_next_icon&32.png"
            editable: documentListView === null || index === documentListView.currentIndex
            selectable: documentListView !== null && index === documentListView.currentIndex
            onItemClicked: documentListView.currentIndex = index
        }
    }
}
