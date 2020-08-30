
import QtQuick 2.12
import QtQuick.Controls 2.5

Pane {
    property alias item: textField
    property alias text: textField.text
    property Component button: null
    readonly property int internalWidth: metrics.paramSectionWidth - 5*leftPadding - 2*rightPadding - 2

    Grid {
        verticalItemAlignment: Grid.AlignVCenter
        rows: 1

        TextField {
            id: textField
            width: internalWidth - (button !== null ? helperButton.width + spacer.width : 0)
        }
        Item {
            id: spacer
            height: 1
            width: padding
            visible: button !== null
        }
        Loader {
            id: helperButton
            sourceComponent: button
        }
    }
}
