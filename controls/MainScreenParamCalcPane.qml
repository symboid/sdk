
import QtQuick 2.12
import QtQuick.Controls 2.5

CalcPane {

    property string title: ""
    height: pane.height
    width: pane.width

    default property alias items: column.children

    Pane {
        id: pane
        bottomPadding: 0
        width: metrics.paramSectionWidth
        GroupBox {
            padding: 0
            anchors.left: parent.left
            anchors.right: parent.right
            background: null

            label: Label {
                width: parent.width - 2*parent.padding
                text: title + ":"
                font.italic: true
                font.bold: true
            }

            Grid {
                id: column
                anchors.right: parent.right
                padding: 1

                columns: 1
                horizontalItemAlignment: Grid.AlignRight
            }
        }
    }
}
