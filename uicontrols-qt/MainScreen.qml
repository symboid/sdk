
import QtQuick 2.12
import QtQuick.Controls 2.5

IndirectContainer {

    readonly property QtObject metrics: QtObject {
        readonly property bool isLandscape: width > height
        readonly property int mandalaSize: isLandscape ? height : width
        readonly property int screenSize: isLandscape ? width : height
        readonly property int restSize: screenSize - mandalaSize

        readonly property int minParamSectionWidth: 300
        readonly property int paramSectionWidth:
            metrics.isLandscape ? ((metrics.restSize / 2) < minParamSectionWidth ? minParamSectionWidth : metrics.restSize / 2)
                                : ((metrics.mandalaSize / 2) < minParamSectionWidth ? metrics.mandalaSize : metrics.mandalaSize / 2)
        readonly property int paramSectionPadding: 20

        readonly property int defaultItemWidth: paramSectionWidth - 3 * paramSectionPadding
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

            width: metrics.isLandscape ? childrenRect.width : metrics.mandalaSize
            height: metrics.isLandscape ? metrics.mandalaSize : childrenRect.height

            flow: metrics.isLandscape ? Flow.TopToBottom : Flow.LeftToRight
        }
    }
}
