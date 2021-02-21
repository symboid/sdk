
import QtQuick 2.12
import QtQuick.Controls 2.5

ControlListItem {
    property alias title: titleLabel.text
    property alias expanded: expandButton.checked

    mainItem: Label {
        id: titleLabel
    }
    rightItem: RoundButton {
        id: expandButton
        checkable: true
        icon.source: expanded ? "/icons/br_up_icon&24.png" : "/icons/br_down_icon&24.png"
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
