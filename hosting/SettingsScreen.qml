
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Symboid.Sdk.Controls 1.0
import QtQuick.Controls.Material 2.12

IndirectContainer {
    id: settingsScreen
    container: panesColumn

    signal backClicked

    Flickable {
        anchors.fill: parent
        clip: true
        flickableDirection: Flickable.VerticalFlick
        contentWidth: panesColumn.width
        contentHeight: panesColumn.height
        Column {
            id: panesColumn
            anchors.horizontalCenter: parent.horizontalCenter
            width: settingsScreen.width
        }
    }
}
