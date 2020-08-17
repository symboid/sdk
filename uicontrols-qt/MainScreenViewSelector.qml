
import QtQuick 2.12
import QtQuick.Controls 2.5

MainScreenBottomPane {
    property var viewNames: []
    property int currentIndex: 0
    controlItem: SpinBox {
        id: viewSpin
        to: viewNames.length - 1
        onValueChanged: currentIndex = value
        textFromValue: function(value, locale)
        {
            return viewNames[value]
        }

        down.indicator: Image {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            opacity: viewSpin.value > viewSpin.from ? 1.0 : 0.1
            source: "/icons/br_prev_icon&24.png"
        }
        up.indicator: Image {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            opacity: viewSpin.value < viewSpin.to ? 1.0 : 0.1
            source: "/icons/br_next_icon&24.png"
        }
    }
}
