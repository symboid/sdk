
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Network 1.0
import Symboid.Sdk.Hosting 1.0

Item {
    id: loadScreen

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: false
    }

    RestTableModel {
        id: softwareModel
        isResultCompact: true
        restClient: RestClient {
            apiAddress: "http://db.symboid.com/live.php"
//                authUser: "symboid_hosting"
//                authPass: "K0rtefa"
        }
        operation: "software?transform=t1&filter=id,eq,1001" //"&filter=platform,eq,win_x64"
//        operation: "software?transform=t1&filter=id,eq," + SoftwareUpdate.appSwid
        onModelAboutToBeReset: busyIndicator.running = true
        onModelReset: busyIndicator.running = false
        onSuccessfullyFinished: {
            if (softwareUpdateFound)
            {
                loadState = "confirm_update"

                console.log("Software update found.")
                console.log("     Current version = " + currentVersion)
                console.log("      Update version = " + updateVersion)
                console.log("          Update URL = " + updateUrl)
            }
            else
            {
                console.log("No software update found.")
            }
        }
        onNetworkError: {
            console.error("Network error fetching software update info!")
        }
        Component.onCompleted: {
            if (AppConfig.software.update_method === SoftwareConfig.UpdateManual) {
                console.log("Checking for software update...")
                runOperation()
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

    property bool softwareUpdateFound: SoftwareUpdate.appVersion.serial < softwareModel.updateSerial

    property alias loadState: loadScreen.state
    state: "continue"
    states: [
        State {
            name: "continue"
            PropertyChanges {
            }
        },
        State {
            name: "confirm_update"
            PropertyChanges {
            }
        },
        State {
            name: "download_update"
            PropertyChanges {
            }
        }
    ]

    Frame {
        anchors.centerIn: parent
        padding: 50
        topPadding: 50
        bottomPadding: 50

        Column {
            spacing: 20
            Label {
                id: loadMessage
                anchors.horizontalCenter: parent.horizontalCenter
                text: {
                    switch (loadState)
                    {
                    case "continue": return qsTr("Loading...")
                    case "confirm_update": return qsTr("Software update found!")
                    case "download_update": return qsTr("Downloading update...")
                    }
                }
                padding: 15
                leftPadding: 50
                rightPadding: leftPadding
                background: Rectangle {
                    color: softwareUpdateFound ? "lightgreen" : "lightsteelblue"
                    radius: 10
                }

                font {
                    pointSize: 24
                    italic: true
                }
            }
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20
                Button {
                    visible: loadState === "confirm_update"
                    text: qsTr("Skip")
                    onClicked: load()
                }
                Button {
                    visible: loadState === "confirm_update"
                    text: qsTr("Apply")
                    onClicked: loadState = "download_update"
                }
                Button {
                    visible: loadState === "download_update"
                    text: qsTr("Cancel")
                }
            }
        }
    }

    Timer {
        interval: 100
        running: !softwareUpdateFound
        onTriggered: load()
    }

    function load()
    {
        console.info("Loading main screen...")
        loadMainScreen()
    }

    signal loadMainScreen
}
