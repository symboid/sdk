
import QtQuick 2.12
import QtQuick.Controls 2.5

IndirectContainer {

    readonly property QtObject metrics: QtObject {
        readonly property int screenWidth: width
        readonly property int screenHeight: height
        readonly property bool isLandscape: screenWidth > screenHeight
        readonly property int mandalaSize: isLandscape ? screenHeight : screenWidth
        readonly property int screenSize: isLandscape ? screenWidth : screenHeight
        readonly property int restSize: screenSize - mandalaSize

        readonly property int minParamSectionWidth: 250
        readonly property int paramSectionWidth:
            isLandscape ? ((restSize / 2) < minParamSectionWidth ? minParamSectionWidth : restSize / 2)
                        : ((mandalaSize / 2) < minParamSectionWidth ? mandalaSize : mandalaSize / 2)
    }

    container: screenFlow

    Flickable {
        anchors.fill: parent

        flickableDirection: metrics.isLandscape ? Flickable.HorizontalFlick : Flickable.VerticalFlick
        contentWidth: screenFlow.width
        contentHeight: screenFlow.height
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        Flow {
            id: screenFlow

            width: metrics.isLandscape ? childrenRect.width : metrics.screenWidth
            height: metrics.isLandscape ? metrics.screenHeight : childrenRect.height

            flow: metrics.isLandscape ? Flow.TopToBottom : Flow.LeftToRight
        }
    }
}
