
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Dox 1.0

Drawer {

    id: documentDialog
    property Document currentDocument: emptyDocument
    Document {
        id: emptyDocument
    }

    property alias operations: operationsView.operations

    InputOperationsView {
        id: operationsView
        anchors.fill: parent
        leftAligned: edge === Qt.LeftEdge
    }
}
