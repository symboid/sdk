
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Network 1.0
import Symboid.Sdk.Hosting 1.0

ProcessPage {
    id: softwareUpdatePage

    signal updateCanceled

    state: "downloading"

    states: [
        State {
            name: "downloading"
            PropertyChanges {
                target: updateMessage
                text: qsTr("Downloading software update...")
            }
            PropertyChanges {
                target: updateButton
                text: qsTr("Cancel")
                onClicked: {
                    softwareUpdateDownloader.cancel()
                    console.info("Software update canceled...")
                }
            }
        },
        State {
            name: "download_error"
            PropertyChanges {
                target: updateMessage
                text: qsTr("Download has been failed!")
            }
            PropertyChanges {
                target: updateButton
                text: qsTr("Continue")
                onClicked: {
                    updateCanceled()
                }
            }
        },
        State {
            name: "completed"
            PropertyChanges {
                target: updateMessage
                text: qsTr("Software update is ready to install.")
            }
            PropertyChanges {
                target: updateButton
                text: qsTr("Restart and install")
                onClicked: {
                    if (SoftwareUpdate.execUpdater(softwareUpdateDownloader.localPath))
                    {
                        console.info("Updater started successfully. Quitting...")
                        Qt.quit()
                    }
                    else
                    {
                        console.error("Updater cannot be started!")
                        softwareUpdatePage.state = "install_error"
                    }
                }
            }
        },
        State {
            name: "install_error"
            PropertyChanges {
                target: updateMessage
                text: qsTr("Software update cannot be executed!")
            }
            PropertyChanges {
                target: updateButton
                text: qsTr("Continue")
                onClicked: {
                    updateCanceled()
                }
            }
        }
    ]

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
                    id: updateMessage
                    font.pointSize: 18
                    wrapMode: Label.WordWrap
                }
            }

            Pane {
                anchors.horizontalCenter: parent.horizontalCenter
                contentItem: ProgressBar {
                    width: 700
                    value: softwareUpdateDownloader.progressPercent
                }
            }
            HorizontalLine {
                anchors.left: parent.left
                anchors.right: parent.right
            }
            Pane {
                anchors.horizontalCenter: parent.horizontalCenter
                contentItem: Button {
                    id: updateButton
                }
            }
        }
    }

    FileDownloader {
        id: softwareUpdateDownloader
        downloadUrl: SoftwareUpdateObject.updateUrl
        onDownloadFailed: {
            state = "download_error"
        }
        onDownloadCompleted: {
            state = "completed"
        }
        onDownloadCanceled: {
            updateCanceled()
        }
    }

    function startUpdate()
    {
        state = "downloading"
        softwareUpdateDownloader.start()
    }
}
