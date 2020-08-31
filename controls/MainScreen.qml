
import QtQuick 2.12
import QtQuick.Controls 2.5

IndirectContainer {

    readonly property QtObject metrics: QtObject {
        readonly property int screenWidth: width
        readonly property int screenHeight: height - toolBar.height
        readonly property bool isLandscape: screenWidth > screenHeight
        readonly property int mandalaSize: isLandscape ? screenHeight : screenWidth
        readonly property int screenSize: isLandscape ? screenWidth : screenHeight
        readonly property int restSize: screenSize - mandalaSize

        readonly property int minParamSectionWidth: 300
        readonly property int paramSectionWidth:
            metrics.isLandscape ? ((metrics.restSize / 2) < minParamSectionWidth ? minParamSectionWidth : metrics.restSize / 2)
                                : ((metrics.mandalaSize / 2) < minParamSectionWidth ? metrics.mandalaSize : metrics.mandalaSize / 2)
    }

    container: screenFlow
    reparentFrom: 2

    property alias toolButtons: toolButtonRepeater.model
    ScreenToolBar {
        id: toolBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        Row {
            Repeater {
                id: toolButtonRepeater
                delegate: ToolButton {
                    icon.source: toolIcon
                    onClicked: toolOperation()
                }
            }
        }
    }

    Flickable {
        anchors {
            top: toolBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        flickableDirection: metrics.isLandscape ? Flickable.HorizontalFlick : Flickable.VerticalFlick
        contentWidth: screenFlow.width
        contentHeight: screenFlow.height
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        Flow {
            id: screenFlow

            width: metrics.isLandscape ? childrenRect.width : metrics.mandalaSize
            height: metrics.isLandscape ? metrics.mandalaSize : childrenRect.height

            flow: metrics.isLandscape ? Flow.TopToBottom : Flow.LeftToRight
        }
    }
}
