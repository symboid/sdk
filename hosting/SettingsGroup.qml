
import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
    property alias title: titleText.text
    property bool collapsed: false

    spacing: 10
    width: parent !== null ? parent.columnWidth : 200

    Rectangle {
        height: 1
        width: parent.width
        color: "grey"
    }
    Row {
        spacing: 10
        RoundButton {
            id: titleButton
            checkable: true
            checked: !collapsed
            onToggled: collapsed = !collapsed
            icon.source: collapsed ? "/icons/br_next_icon&24.png" : "/icons/br_down_icon&24.png"
            width:36;height:36
        }
        Label {
            id: titleText
            font.bold: true
            font.italic: true
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: collapsed = !collapsed
            }
        }
    }
    Rectangle {
        height: 1
        width: parent.width
        color: "grey"
    }

    onChildrenChanged: {
        if (children.length > 3)
        {
            var newChild = children[children.length - 1]
            newChild.visible = Qt.binding(function(){return !collapsed})
        }
    }
}
