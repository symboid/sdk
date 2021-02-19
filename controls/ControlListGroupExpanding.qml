
import QtQuick 2.12
import QtQuick.Controls 2.5

ControlListGroup {
    property alias expanded: expandButton.checked

    leftItem: RoundButton {
        id: expandButton
        checkable: true
        radius: height / 6
        icon.source: expanded ? "/icons/br_down_icon&24.png" : "/icons/br_next_icon&24.png"
        background: null
    }

    onChildrenChanged: {
        if (children.length > 0)
        {
            var newChild = children[children.length - 1]
            newChild.visible = Qt.binding(function(){return expanded})
            if (newChild instanceof ControlListItem)
            {
                newChild.indented = true
            }
        }
    }
}
