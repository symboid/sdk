
import QtQuick 2.12
import QtQuick.Controls 2.5

Flow {
    property string title: ""
    property int minimumColumnWidth: 400
    readonly property int numberOfColumns: (width - 2*padding + spacing) / (minimumColumnWidth + spacing)
    readonly property int columnWidth: (width - 2*padding - (numberOfColumns-1)*spacing) / numberOfColumns
    padding: 20
    spacing: 20
}
/*
Container {
    property string title: ""
    property int minimumColumnWidth: 400
    readonly property int columnWidth: flow.columnWidth
    contentItem: Flickable {
        anchors.fill: parent
        clip: true
        flickableDirection: Flickable.VerticalFlick
        contentWidth: flow.width
        contentHeight: flow.height
        Flow {
            id: flow
            readonly property int numberOfColumns: (width - 2*padding + spacing) / (minimumColumnWidth + spacing)
            readonly property int columnWidth: (width - 2*padding - (numberOfColumns-1)*spacing) / numberOfColumns
            padding: 20
            spacing: 20
        }
    }
    onChildrenChanged: {
        var newChildIndex = 1
        if (children.length > newChildIndex)
        {
            var newChild = children[newChildIndex]
            newChild.parent = null
            flow.children.push(newChild)
            children.length = newChildIndex
        }
    }
}
*/
