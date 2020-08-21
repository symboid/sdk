
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Symboid.Sdk.Controls 1.0
import QtQuick.Controls.Material 2.12

IndirectContainer {

    signal backClicked

    ToolBar {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        Material.primary: "#95B2A0"

        ToolButton {
            icon.source: "/icons/br_prev_icon&32.png"
            onClicked: backClicked()
        }
    }

    TabBar {
        id: tabBar
        anchors {
            top: parent.top
            left: backButton.right
            right: parent.right
        }
        Component {
            id: tabButtonComponent
            TabButton {
            }
        }
    }
    onNewChildAdded: {
        var tabButtonObject = tabButtonComponent.createObject(tabBar, { text: newChild.title })
        if (tabButtonObject !== null)
        {
            tabBar.addItem(tabButtonObject)
        }
    }

    reparentFrom: 3
    container: stackLayout
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
}
