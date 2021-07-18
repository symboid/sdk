
import QtQuick 2.12
import Symboid.Sdk.Controls 1.0

FolderView {

    property int docPageCount: 0
    signal switchDocPage(int pageIndex)
    signal docPageLoaded

    property FolderView folderView: this
    initialItem: FolderPane {
        Repeater {
            model: docPageCount
            DocMethodItem {
                title: qsTr("Page %1").arg(index)
                onLoadClicked: {
                    switchDocPage(index)
                    docPageLoaded()
                }
            }
        }
    }
}
