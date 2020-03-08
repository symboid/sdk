
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

ListView {
    property alias filterText: documentFolderModel.filterText
    property string selectedPath: ""

    clip: true
    DocumentFolderModel {
        id: documentFolderModel
        onFilterTextChanged: {
            selectedPath = ""
            currentIndex = -1
        }
    }
    model: documentFolderModel
    currentIndex: -1
    delegate: Pane {
        Label {
            text: documentTitle
        }
        width: parent.width
        background: Rectangle {
            color: index == currentIndex ? "lightgray" : "transparent"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    currentIndex = index
                    selectedPath = documentPath
                }
            }
        }

    }
}
