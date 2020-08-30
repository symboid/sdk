
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Pane {
    property Item referenceItem: Item {}
    property Item controlItem: Item {}

    width: metrics.paramSectionWidth

    readonly property int itemHeight: itemSlot.height + 2*padding
    readonly property int landscapeSpace: metrics.mandalaSize - (referenceItem.y + referenceItem.height)

    height:        !metrics.isLandscape ? itemHeight :
            landscapeSpace < itemHeight ? metrics.mandalaSize :
                                          landscapeSpace

    ItemSlot {
        id: itemSlot
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        item: controlItem
    }
}
