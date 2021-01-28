
import QtQuick 2.12
import QtQuick.Controls 2.5

IndirectContainer {
    property MainScreenMetrics metrics: MainScreenMetrics {
        screenWidth: width
        screenHeight: height
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
