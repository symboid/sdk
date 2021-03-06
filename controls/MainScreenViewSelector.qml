
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import QtQuick.Layouts 1.12

Column {
    property alias mainIndex: mainViewSelector.currentIndex
    readonly property var subViewSelector: subViewSelectors.itemAt(mainIndex)
    readonly property int subIndex: subViewSelector !== null ? subViewSelector.currentIndex : 0
    readonly property alias minWidth: mainViewSelector.minWidth

    property var viewTitles: []

    SingleViewSelector {
        id: mainViewSelector
        anchors.left: parent.left
        anchors.right: parent.right
        labelFont.bold: true
        viewNames: {
            var names = []
            for (var v = 0; v < viewTitles.length; ++v)
            {
                names.push(viewTitles[v].main)
            }

            return names
        }
    }
    StackLayout {
        width: mainViewSelector.width
        height: mainViewSelector.height
        scale: 0.9
        currentIndex: mainIndex
        Repeater {
            id: subViewSelectors
            model: viewTitles.length
            delegate: Item {
                property alias currentIndex: subViewSelector.currentIndex
                SingleViewSelector {
                    id: subViewSelector
                    labelFont.italic: true
                    anchors.left: parent.left
                    anchors.right: parent.right
                    viewNames: viewTitles[index].sub
                }
            }
        }
    }
}
