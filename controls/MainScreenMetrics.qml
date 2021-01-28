
import QtQuick 2.12

QtObject {
    required property int screenWidth
    required property int screenHeight

    readonly property bool isLandscape: screenWidth > screenHeight
    readonly property bool isPortrait: !isLandscape
    readonly property int screenSize: isLandscape ? screenWidth : screenHeight

    property int minParamSectionWidth: 250
    property int paramSectionWidth: minParamSectionWidth

    property bool isTransLandscape: false
}
