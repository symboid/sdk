
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

ListView {
    property alias filterText: documentFolderModel.filterText
    clip: true
    DocumentFolderModel {
        id: documentFolderModel
    }
    model: documentFolderModel
    delegate: Pane {
        Label {
            text: documentTitle
        }
    }
}
