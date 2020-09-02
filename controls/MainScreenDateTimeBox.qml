
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

    property alias showTimeBox: timeBox.visible
    property alias showCurrentTimer: currentTimer.visible
    readonly property alias unixTime: unixTimeConverter.unixTime
    property alias currentTimerOn: currentTimer.checked
    property alias showSeconds: timeBox.showSeconds

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
        id: currentTimer
        text: qsTr("Current")
        visible: false
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
    function setDate(year,month,day)
    {
        dateBox.setDate(year,month,day)
    }
    function setTime(hour,minute,second)
    {
        timeBox.setTime(hour,minute,second)
    }
    function setCurrent()
    {
        dateBox.setCurrent()
        timeBox.setCurrent()
    }
}
