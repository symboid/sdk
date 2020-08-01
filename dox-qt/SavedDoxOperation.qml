
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Dox 1.0

InputOperation {

    property Document currentDocument: null
    signal documentSaved

    control: DocumentFolderBox {
        id: documentFolderBox
        height: 300
    }
    canExec: documentFolderBox.selectedDocumentPath != ""
    onExec: {
        currentDocument.filePath = documentFolderBox.selectedDocumentPath
        currentDocument.load()
    }
    execPane: Column {
        RoundButton {
            icon.source: "/icons/arrow_left_icon&24.png"
            onClicked: {
                currentDocument.title = documentFolderBox.documentTitle
                currentDocument.filePath = documentFolderBox.selectedDocumentPath
                currentDocument.save()
                documentFolderBox.updateModel()
                documentSaved()
            }
            enabled: documentFolderBox.documentTitle !== ""
        }
    }
    function init(newTitle)
    {
        documentFolderBox.documentTitle = newTitle
        documentFolderBox.documentIndex = -1
        documentFolderBox.selectedDocumentPath = ""
    }
}
