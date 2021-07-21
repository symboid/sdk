
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

FolderView {

    property int docPageCount: 0
    signal switchDocPage(int pageIndex)
    signal docPageLoaded()

    property FolderView folderView: this
    initialItem: FolderPane {
        Repeater {
            model: docPageCount
            FolderItem {
                title: qsTr("Page %1").arg(index)

                rightItem: RoundButton {
                    radius: height / 9
                    icon.source: "/icons/br_next_icon&24.png"
                    onClicked: {
                        switchDocPage(index)
                        docPageLoaded()
                    }
                }
            }
        }
    }
}
