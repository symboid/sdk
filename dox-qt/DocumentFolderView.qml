
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Dox 1.0

ListView {
    model: DocumentFolderModel {
    }
    delegate: Label {
        text: display
    }
}
