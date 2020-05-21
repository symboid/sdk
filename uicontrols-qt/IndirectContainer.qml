
import QtQuick 2.12
import QtQuick.Controls 2.5

Item {

    property int reparentFrom: 1
    property Item container: null

    onChildrenChanged: {
        if (children.length > reparentFrom)
        {
            children[reparentFrom].parent = container
            children.length = reparentFrom
        }
    }
}
