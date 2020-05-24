
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {
    container: flow

    property string title: ""
    property int minimumColumnWidth: 400

    Flickable {
        anchors.fill: parent
        clip: true
        flickableDirection: Flickable.VerticalFlick
        contentWidth: parent.width
        contentHeight: flow.height
        Flow {
            id: flow
            width: parent.width
            readonly property int numberOfColumns: (width - 2*padding + spacing) / (minimumColumnWidth + spacing)
            readonly property int columnWidth: (width - 2*padding - (numberOfColumns-1)*spacing) / numberOfColumns
            padding: 20
            spacing: 20
        }
    }
}
