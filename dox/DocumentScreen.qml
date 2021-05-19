
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0
import Symboid.Sdk.Controls 1.0

FolderScreen {
    id: documentScreen
    initialTitle: qsTr("Horoscopes and calculations")
    property alias settingsView: documentScreen.folderView

    FolderGroupFixed {
        title: qsTr("Methods")

        FolderGroupExpanding {
            title: qsTr("Forecasts")
            DocumentItem {
                title: qsTr("Primary direction")
            }
            DocumentItem {
                title: qsTr("Transit")
            }
        }

        FolderGroupExpanding {
            title: qsTr("Revolutions")
            DocumentItem {
                title: qsTr("Solar horoscope")
            }
            DocumentItem {
                title: qsTr("Lunar horoscope")
            }
        }
    }

    FolderGroupFixed {
        title: qsTr("Saved results")
    }

}
