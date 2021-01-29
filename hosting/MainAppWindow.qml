
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0

ApplicationWindow {

    property string mainPageUrl: ""

    visible: true
    visibility: Window.Maximized
    width: 900
    height: 600

    ProcessView {
        id: loadProcess
        anchors.fill: parent
        LoadingPage {
            id: loadingPage
            onLoadMainPage: {
                console.info("Loading main page...")
                mainScreenLoader.source = mainPageUrl
            }
            onLoadSoftwareUpdatePage: {
                loadProcess.currentIndex = 1
                softwareUpdatePage.startUpdate()
            }
        }
        SoftwareUpdatePage {
            id: softwareUpdatePage
            onUpdateCanceled: {
                console.info("Loading main page...")
                mainScreenLoader.source = mainPageUrl
            }
        }
        Loader {
            id: mainScreenLoader
            onLoaded: {
                console.info("Main page loaded.")
                loadProcess.currentIndex = 2
                loadingPage.stopAnimation()
            }
        }
    }
}
