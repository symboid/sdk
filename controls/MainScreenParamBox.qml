
import QtQuick 2.12
import QtQuick.Controls 2.5

Grid {
    property string title: ""

    width: metrics.paramSectionWidth
    padding: metrics.paramSectionPadding
    columns: 1
    horizontalItemAlignment: Grid.AlignRight

    Label {
        id: titleLabel
        width: parent.width - 2*parent.padding
        text: title + ":"
        font.italic: true
        font.bold: true
    }
}
