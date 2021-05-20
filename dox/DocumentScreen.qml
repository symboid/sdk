
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0
import Symboid.Sdk.Controls 1.0

FolderScreen {
    id: documentScreen
    initialTitle: qsTr("Horoscopes and tabulars")
    property alias settingsView: documentScreen.folderView

    DocumentItem {
        title: qsTr("Natal horoscope")
    }
}
