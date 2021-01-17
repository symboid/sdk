
import QtQuick.Controls 2.5

LoadListItem {
    property alias selectIndicator: selected.indicator
    property alias selected: selected.checked
    property alias selectorVisible: selected.visible
    property bool selectable: false

    rightItem: CheckBox {
        id: selected
    }
}
