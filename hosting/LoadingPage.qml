
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Network 1.0
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

ProcessPage {

    signal loadMainPage
    signal loadSoftwareUpdatePage

    MessageDialog {
        id: softwareUpdateConfirm
        message: qsTr("Software update is available. Do you want to process?")
        standardButtons: DialogButtonBox.Yes | DialogButtonBox.No
        onAccepted: loadSoftwareUpdatePage()
        onRejected: loadMainPage()
    }

    Component.onCompleted: {
        SoftwareUpdateObject.softwareUpdateFound = softwareUpdateConfirm.open
        SoftwareUpdateObject.softwareUpdateNotFound = loadMainPage

        if (AppConfig.software.update_method === SoftwareConfig.UpdateManual) {
            console.log("Checking for software update...")
            SoftwareUpdateObject.runOperation()
        }
        else {
            loadMainPage()
        }
    }

    contentItem: Item {
        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            HorizontalLine {
                anchors.left: parent.left
                anchors.right: parent.right
            }
            Pane {
                anchors.horizontalCenter: parent.horizontalCenter
                contentItem: Label {
                    anchors.centerIn: parent
                    text: qsTr("Loading...")
                    font {
                        pointSize: 24
                        bold: true
                        italic: true
                    }
                }
            }
            HorizontalLine {
                anchors.left: parent.left
                anchors.right: parent.right
            }
            Pane {
                anchors.horizontalCenter: parent.horizontalCenter
                BusyIndicator {
                    running: true
                }
            }
        }
    }
}
