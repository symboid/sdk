
import QtQuick 2.12
import QtQuick.Controls 2.12
import Symboid.Sdk.Controls 1.0

InputOperation {

    property alias itemModel: recentItems.model
    property Component itemComponent: Label {
        text: inputItemTitle
        leftPadding: 20
    }

    signal itemSelected(int itemIndex)

    withButtons: false

    control: ListView {
        id: recentItems
        height: Math.min(contentHeight,500)
        delegate: Column {
            Row {
                Loader {
                    readonly property string inputItemTitle: itemTitle
                    readonly property int itemSpace: parent.width
                    sourceComponent: itemComponent
                    anchors.verticalCenter: parent.verticalCenter
                    width: recentItems.width - loadButton.width
                }
                RoundButton {
                    id: loadButton
                    anchors.verticalCenter: parent.verticalCenter
                    icon.source: leftAligned ? "/icons/arrow_right_icon&24.png"
                                        : "/icons/arrow_left_icon&24.png"
                    onClicked: {
                        recentItems.currentIndex = index
                        itemSelected(index)
                        exec()
                        finishExec()
                    }
                }
            }
            Rectangle {
                height: 1
                width: parent.width
                color: "lightgray"
                visible: index < recentItems.count - 1
            }
        }
    }
    canExec: recentItems.currentIndex != -1
}
