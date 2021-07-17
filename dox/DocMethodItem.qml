
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

FolderItem {

    signal loadClicked

    rightItem: RoundButton {
        radius: height / 9
        icon.source: "/icons/br_next_icon&24.png"
        onClicked: loadClicked()
    }

}
