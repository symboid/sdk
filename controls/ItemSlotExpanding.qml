
import QtQuick 2.12
import QtQuick.Layouts 1.12

StackLayout {
    property Item contentItem: null
    onContentItemChanged: children = contentItem !== null ? [ contentItem ] : []
    width: contentItem !== null ? contentItem.width : 0
    height: contentItem !== null ? contentItem.height : 0
}
