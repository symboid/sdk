
import QtQuick 2.12
import QtQuick.Controls 2.5

Flow {
    property string title: ""
    readonly property int minimumColumnWidth: 400
    readonly property int numberOfColumns: (width - 2*padding + spacing) / (minimumColumnWidth + spacing)
    readonly property int columnWidth: (width - 2*padding - (numberOfColumns-1)*spacing) / numberOfColumns
    padding: 20
    spacing: 20
}
