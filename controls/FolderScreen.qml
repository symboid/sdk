
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

IndirectContainer {

    container: firstPane
    reparentFrom: 2

    property string initialTitle: ""
    property alias initialPane: fv.initialItem
    property bool withBackButton: false
    signal backButtonClicked

    ToolBar {
        id: toolbar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        ToolButton {
            icon.source: "/icons/br_prev_icon&32.png"
            enabled: folderView.depth > 1 || withBackButton
            onClicked: {
                if (folderView.depth > 1)
                {
                    folderView.pop()
                }
                else if (withBackButton)
                {
                    backButtonClicked()
                }
            }
        }
        Label {
            anchors.centerIn: parent
            text: folderView.currentItem !== null ? folderView.currentItem.title : ""
            font.italic: true
        }
    }

    property FolderView folderView: fv
    FolderView {
        id: fv
        anchors {
            top: toolbar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        initialItem: FolderPane {
            id: firstPane
            title: initialTitle
        }
        function loadPane(paneComponent)
        {
            var pane = null
            if (paneComponent)
            {
                pane = paneComponent.createObject(folderView,{})
                folderView.push(pane)
            }
            return pane
        }
    }
}
