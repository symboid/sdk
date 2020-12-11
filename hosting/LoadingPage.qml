
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Network 1.0
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

ProcessPage {

    MessageDialog {
        id: softwareUpdateConfirm
        message: qsTr("Software update is available. Do you want to process?")
        standardButtons: DialogButtonBox.Yes | DialogButtonBox.No
        onAccepted: loadSoftwareUpdatePage()
        onRejected: loadMainPage()
    }

    RestTableModel {
        isResultCompact: true
        restClient: RestClient {
            apiAddress: "http://db.symboid.com/live.php"
//                authUser: "symboid_hosting"
//                authPass: "K0rtefa"
        }
        operation: "software?transform=t1&filter=id,eq,1001" //"&filter=platform,eq,win_x64"
//        operation: "software?transform=t1&filter=id,eq," + SoftwareUpdate.appSwid
        onSuccessfullyFinished: {
            if (SoftwareUpdate.appVersion.serial < updateSerial)
            {
                console.log("Software update found.")
                console.log("     Current version = " + currentVersion)
                console.log("      Update version = " + updateVersion)
                console.log("          Update URL = " + updateUrl)
                softwareUpdateConfirm.open()
            }
            else
            {
                console.log("No software update found.")
                loadMainPage()
            }
        }
        onNetworkError: {
            console.error("Network error fetching software update info!")
            loadMainPage()
        }
        Component.onCompleted: {
            if (AppConfig.software.update_method === SoftwareConfig.UpdateManual) {
                console.log("Checking for software update...")
                runOperation()
            }
            else {
                loadMainPage()
            }
        }

        readonly property string currentVersion:
            SoftwareUpdate.appVersion.major + "." + SoftwareUpdate.appVersion.minor + "." +
            SoftwareUpdate.appVersion.patch + "." + SoftwareUpdate.appVersion.serial
        readonly property int updateSerial: objectCount > 0 ? firstObject.serial_num : 0
        readonly property string updateVersion: objectCount > 0 ?
                firstObject.ver_major + "." + firstObject.ver_minor + "." + firstObject.ver_patch + "." + firstObject.serial_num  : ""
        readonly property string updateUrl: objectCount > 0 ? firstObject.dl_location : ""
    }

    signal loadMainPage
    signal loadSoftwareUpdatePage

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
