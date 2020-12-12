pragma Singleton
import Symboid.Sdk.Network 1.0
import Symboid.Sdk.Hosting 1.0

RestTableModel {

    property var softwareUpdateFound: function(){}
    property var softwareUpdateNotFound: function(){}

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
    readonly property int updateSerial: objectCount > 0 ? firstObject.serial_num : 0
    readonly property string updateVersion: objectCount > 0 ?
            firstObject.ver_major + "." + firstObject.ver_minor + "." + firstObject.ver_patch + "." + firstObject.serial_num  : ""
    readonly property string updateUrl: objectCount > 0 ? firstObject.dl_location : ""
}
