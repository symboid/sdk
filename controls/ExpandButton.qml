
import QtQuick.Controls 2.5

RoundButton {
    property bool expanded: false
    property bool rightHandSide: false
    icon.source: expanded ? "/icons/br_down_icon&24.png" :
            rightHandSide ? "/icons/br_prev_icon&24.png" :
                            "/icons/br_next_icon&24.png"
    onClicked: expanded = !expanded
}
