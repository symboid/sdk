
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Dox 1.0

RecentInputOperation {

    property Document currentDocument: null

    itemModel: RecentDoxModel {
        id: recentDoxModel
    }

    property string selectedFilePath: ""
    onItemSelected: {
        var index = recentDoxModel.index(itemIndex, 0)
        var role = RecentDoxModel.DocumentPath
        selectedFilePath = itemModel.data(index, role)
    }

    onExec: {
        if (selectedFilePath != "")
        {
            currentDocument.filePath = selectedFilePath
            currentDocument.load()
        }
    }

    function add(docTitle, docFilePath)
    {
        recentDoxModel.add(docTitle, docFilePath)
    }
}
