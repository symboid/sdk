
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Pane {
    property Item referenceItem: Item {}
    property alias controlItem: itemSlot.contentItem

    width: metrics.paramSectionWidth

    readonly property int itemHeight: itemSlot.height + 2*padding
    readonly property int landscapeSpace: metrics.screenHeight - (referenceItem.y + referenceItem.height)

    contentItem: Column {
        Item {
            width: 1
            height:        !metrics.isLandscape ? 0 :
                    landscapeSpace < itemHeight ? metrics.screenHeight - itemHeight :
                                                  landscapeSpace - itemHeight
        }

        ItemSlotExpanding {
            id: itemSlot
            anchors.left: parent.left
            anchors.right: parent.right
            contentItem: controlItem
        }
    }
}
