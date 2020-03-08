
import QtQuick 2.12
import QtQuick.Layouts 1.12

StackLayout {
    property Item item: null
    onItemChanged: children = item !== null ? [ item ] : []
    width: item !== null ? item.width : 0
    height: item !== null ? item.height : 0
}
