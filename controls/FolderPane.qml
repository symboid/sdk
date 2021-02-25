
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {
    property string title: ""
    container: rootFolderNode
    Flickable {
        anchors.fill: parent
        clip: true
        flickableDirection: Flickable.VerticalFlick
        contentWidth: rootFolderNode.width
        contentHeight: rootFolderNode.height
        FolderNode {
            id: rootFolderNode
        }
    }
}
