
import QtQuick 2.12

Grid {
    rows: 1
    columns: 2
    columnSpacing: 10
    verticalItemAlignment: Grid.AlignVCenter
    readonly property int cellWidth: (parent.width - columnSpacing) / 2

    property Item setting: Item {}
    property alias hint: hintText.text

    ItemSlot {
        item: setting
        width: cellWidth
    }

    Text {
        id: hintText
        width: cellWidth
        wrapMode: Text.WordWrap
    }
}
