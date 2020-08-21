
import QtQuick 2.12
import QtQuick.Controls 2.5

Item {

    property int reparentFrom: 1
    property Item container: null

    signal newChildAdded(var newChild)
    onChildrenChanged: {
        if (children.length > reparentFrom)
        {
            var newChild = children[reparentFrom]
            newChild.parent = container
            children.length = reparentFrom
            newChildAdded(newChild)
        }
    }
}
