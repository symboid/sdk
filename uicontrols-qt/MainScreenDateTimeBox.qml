
import QtQuick 2.0
import Symboid.Sdk.Controls 1.0

MainScreenParamBox {

    title: qsTr("Date and time")

    property alias year: dateBox.year
    property alias month: dateBox.month
    property alias day: dateBox.day

    property alias hour: timeBox.hour
    property alias minute: timeBox.minute
    property alias second: timeBox.second

    property bool showDetails: false
    readonly property alias unixTime: unixTimeConverter.unixTime
    property bool currentTimerOn: false

    DateCoordBox {
        id: dateBox
        enabled: !currentTimerOn
        editable: true
    }
    TimeCoordBox {
        id: timeBox
        enabled: !currentTimerOn
        editable: true
        circularLink: dateBox.dayLink
    }
    MainScreenTimer {
        text: qsTr("Current")
        visible: showDetails
        checked: currentTimerOn
        onTriggered: {
            dateBox.setCurrent()
            timeBox.setCurrent()
        }
    }
    UnixTimeConverter {
        id: unixTimeConverter
        year: dateBox.year
        month: dateBox.month
        day: dateBox.day
        hour: timeBox.hour
        minute: timeBox.minute
        second: timeBox.second
    }
}
