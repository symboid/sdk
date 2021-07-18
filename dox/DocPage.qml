
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import QtQml.Models 2.12

MainScreen {

    readonly property int mandalaSize: metrics.isLandscape ? metrics.screenHeight : metrics.screenWidth
    readonly property int restSize: metrics.screenSize - mandalaSize
    readonly property int horzMandalaSpace: metrics.screenWidth - 2 * metrics.minParamSectionWidth

    metrics.isTransLandscape: metrics.isLandscape && horzMandalaSpace < mandalaSize
    metrics.paramSectionWidth:
        metrics.isLandscape ? ((restSize / 2) < metrics.minParamSectionWidth ? metrics.minParamSectionWidth : restSize / 2)
                    : ((mandalaSize / 2) < metrics.minParamSectionWidth ? mandalaSize : mandalaSize / 2)

    property string pageTitle: ""

    StackView.onActivating: loadingPopup.show(pageTitle)

    signal closeView
    RoundButton {
        anchors.top: parent.top
        anchors.right: parent.right
        icon.source: "/icons/delete_icon&24.png"
        background: null
        opacity: 0.5
        onClicked: closeView()
    }
}
