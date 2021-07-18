
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

FolderView {

    property alias fileMenuModel: fileMenuRepeater.model

    signal fileMethodClicked

    property FolderView folderView: this
    initialItem: FolderPane {
        Repeater {
            id: fileMenuRepeater
            FolderItem {
                title: itemTitle
                rightItem: ToolButton {
                    icon.source: itemIcon
                    onClicked: {
                        itemClicked()
                        fileMethodClicked()
                    }
                }
            }
        }
    }
}
