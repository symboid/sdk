
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Dox 1.0

Drawer {

    property Document currentDocument: emptyDocument
    Document {
        id: emptyDocument
    }

    property DocumentFolderBox documentFolderBox: operationsView.operations[0].control

    InputOperationsView {
        id: operationsView
        anchors.fill: parent
        leftAligned: edge === Qt.LeftEdge

        operations: [
            InputOperation {
                title: qsTr("Saved horoscopes")
                control: DocumentFolderBox {
                    id: docFolder
                    height: 300
                }
                canExec: documentFolderBox.selectedDocumentPath != ""
                onExec: {
                    currentDocument.filePath = documentFolderBox.selectedDocumentPath
                    currentDocument.load()
                    close()
                }
                execPane: Column {
                    RoundButton {
                        icon.source: "/icons/arrow_left_icon&24.png"
                        onClicked: {
                            currentDocument.title = documentFolderBox.documentTitle
                            currentDocument.filePath = documentFolderBox.selectedDocumentPath
                            currentDocument.save()
                            documentFolderBox.updateModel()
                            close()
                        }
                        enabled: documentFolderBox.documentTitle !== ""
                    }
                }
            },
            InputOperation {
                title: qsTr("Current transit")
                canExec: true
                onExec: {
                    currentDocument.loadCurrent()
                    close()
                }
            },
            InputOperation {
                title: qsTr("Recent horoscopes")
                control: Rectangle {
                    width: 100
                    height: 100
                    border.width: 1
                    border.color: "red"
                }
            }
        ]
    }
    onOpened: {
        documentFolderBox.documentTitle = currentDocument.title
        documentFolderBox.documentIndex = -1
        documentFolderBox.selectedDocumentPath = ""
    }
    onClosed: {

    }
}
