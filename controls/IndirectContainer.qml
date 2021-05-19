
import QtQuick 2.12
import QtQuick.Controls 2.5

Item {

    property int reparentFrom: 1
    property Item container: null
    property var attachChild: function(newChild)
    {
        if (container)
        {
            newChild.parent = container
        }
    }

    signal newChildAdded(var newChild)
    onChildrenChanged: {
        if (children.length > reparentFrom)
        {
            var newChild = children[reparentFrom]
            newChild.parent = null
            attachChild(newChild)
            children.length = reparentFrom
            newChildAdded(newChild)
        }
    }
}
