
import QtQuick 2.12
import QtQuick.Controls 2.5

FolderGroup {

    rightItem: RoundButton {
        icon.source: "/icons/br_next_icon&24.png"
        onClicked: folderView.loadPane(folderPane)
    }

    property Component folderPane: null
}
