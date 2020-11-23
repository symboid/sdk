
import QtQuick 2.12
import QtQuick.Controls 2.5

SettingsTreeNode {

    property alias title: titleLabel.text
    property alias expanded: expandButton.checked

    SettingsItem {
        setting: Label {
            id: titleLabel
        }
        leftItem: RoundButton {
            id: expandButton
            checkable: true
            radius: height / 6
            text: !expanded ? "+" : "-"
            font.bold: true
        }
    }

    onChildrenChanged: {
        if (children.length > 1)
        {
            var newChild = children[children.length - 1]
            newChild.visible = Qt.binding(function(){return expanded})
            if (newChild instanceof SettingsItem)
            {
                newChild.indented = true
            }
        }
    }
}
