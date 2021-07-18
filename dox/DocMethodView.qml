
import QtQuick 2.12
import Symboid.Sdk.Controls 1.0

FolderView {

    property alias docMethodModel: docMethodRepeater.model

    signal docViewLoaded

    property FolderView folderView: this
    initialItem: FolderPane {
        Repeater {
            id: docMethodRepeater
            DocMethodItem {
                title: methodTitle
                onLoadClicked: {
                    methodLoadClicked()
                    docViewLoaded()
                }
                withSeparator: methodSeparated !== undefined && methodSeparated
            }
        }
    }
}
