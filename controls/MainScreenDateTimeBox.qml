
import QtQuick 2.12
import QtQuick.Controls 2.5
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

    property alias popupParent: dateTimePopup.parent

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
    Pane {
        id: toolsPane
        contentItem: Row {
            spacing: parent.padding
            CheckBox {
                anchors.verticalCenter: parent.verticalCenter
                id: currentTimer
                text: qsTr("Current")
                visible: false
                checkable: true
                onCheckedChanged: {
                    if (checked)
                    {
                        dateBox.setCurrent()
                        timeBox.setCurrent()
                    }
                }
            }
            RoundButton {
                anchors.verticalCenter: parent.verticalCenter
                enabled: !currentTimerOn
                radius: 5
                icon.source: "/icons/calendar_2_icon&32.png"
                onClicked: dateTimePopup.open()
                DateTimePopup {
                    id: dateTimePopup
                    onOpened: {
                        selectedYear = year
                        selectedMonth = month - 1
                        selectedDay = day
                        selectedHour = hour
                        selectedMinute = minute
                        selectedSecond = second
                    }
                    onDateTimeAccepted: {
                        year = selectedYear
                        month = selectedMonth + 1
                        day = selectedDay
                        hour = selectedHour
                        minute = selectedMinute
                        second = selectedSecond
                    }
                }
            }
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
