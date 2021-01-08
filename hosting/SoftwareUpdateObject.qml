pragma Singleton
import Symboid.Sdk.Network 1.0
import Symboid.Sdk.Hosting 1.0
import QtQuick 2.12

RestObjectModel {

    property var softwareUpdateFound: function(){}
    property var softwareUpdateNotFound: function(){}

    isResultCompact: true
    restClient: RestClient {
        apiAddress: "api.symboid.com"
        secure: AppConfig.software.ssl_supported
    }
    operation: "software/%1/%2".arg(SoftwareUpdate.appVersion.name).arg(SoftwareUpdate.platform)
    onSuccessfullyFinished: {
        if (SoftwareUpdate.appVersion.serial < update.serial_num)
        {
            console.log("Software update found.")
            console.log("     Current version = " + currentVersion)
            console.log("      Update version = " + update.ver_major + "." + update.ver_minor + "." +
                                                    update.ver_patch + "." + update.serial_num)
            console.log("          Update URL = " + update.dl_location)
            softwareUpdateFound()
        }
        else
        {
            console.log("No software update found.")
            softwareUpdateNotFound()
        }
    }
    onNetworkError: {
        console.error("Network error fetching software update info!")
        softwareUpdateNotFound()
    }

    readonly property string currentVersion:
        SoftwareUpdate.appVersion.major + "." + SoftwareUpdate.appVersion.minor + "." +
        SoftwareUpdate.appVersion.patch + "." + SoftwareUpdate.appVersion.serial

    readonly property QtObject noneObject: QtObject {
        property int serial_num: 0
        property int ver_major: 0
        property int ver_minor: 0
        property int ver_patch: 0
        property string dl_location: ""
    }
    readonly property var update: isValid ? restObject : noneObject
    readonly property string updateUrl: update.dl_location
}
