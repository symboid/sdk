
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
    TabBar {
        id: tabBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        Component {
            id: tabButtonComponent
            TabButton {
            }
        }
    }
    StackLayout {
        id: stackLayout
        anchors {
            top: tabBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        currentIndex: tabBar.currentIndex
    }
    onChildrenChanged: {
        if (children.length > 2)
        {
            // reparenting new pane
            var newPane = children[2]
            newPane.parent = null
            stackLayout.children.push(newPane)
            children.length = 2
            // adding corresponding tab button
            var tabButtonObject = tabButtonComponent.createObject(tabBar, { text: newPane.title })
            if (tabButtonObject !== null)
            {
                tabBar.addItem(tabButtonObject)
            }
        }
    }
}
