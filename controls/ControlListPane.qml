
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {
    property string title: ""
    container: rootTreeNode
    Flickable {
        anchors.fill: parent
        clip: true
        flickableDirection: Flickable.VerticalFlick
        contentWidth: rootTreeNode.width
        contentHeight: rootTreeNode.height
        ControlListTreeNode {
            id: rootTreeNode
        }
    }
}
