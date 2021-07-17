
import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    // expanding child elements to container
    onChildrenChanged: children[children.length - 1].anchors.fill = this

    // only the current element is visible
    property int currentIndex: -1
    onCurrentIndexChanged: {
        for (var c = 0; c < children.length; ++c)
        {
            children[c].visible = (c === currentIndex)
        }
    }

    // number of elements in container
    readonly property int count: children.length
}
