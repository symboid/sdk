
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Symboid.Sdk.Controls 1.0
import QtQuick.Controls.Material 2.12

IndirectContainer {

    signal backClicked

    ScreenToolBar {
        id: toolBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ToolButton {
            id: backButton
            icon.source: "/icons/br_prev_icon&32.png"
            onClicked: backClicked()
        }

        TabBar {
            id: tabBar
            anchors {
                left: backButton.right
                right: parent.right
            }
            Material.background: "#95B2A0"
            Component {
                id: tabButtonComponent
                TabButton {
                }
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

    reparentFrom: 2
    container: stackLayout
    StackLayout {
        id: stackLayout
        anchors {
            top: toolBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        currentIndex: tabBar.currentIndex
    }
}
