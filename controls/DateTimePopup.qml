
import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.calendar 1.0

Popup {
    anchors.centerIn: parent

    width: Math.min(parent.width - 50, 700)
    height: Math.min(parent.height - 50, 500)

    property int selectedDay: 1
    property int selectedMonth: 0
    property int selectedYear: calcYear()
    onSelectedYearChanged: {
        digit_0.currentIndex = yearDigit(selectedYear,0)
        digit_1.currentIndex = yearDigit(selectedYear,1)
        digit_2.currentIndex = yearDigit(selectedYear,2)
        digit_3.currentIndex = yearDigit(selectedYear,3)
        selectedYear = Qt.binding(function(){return calcYear()})
        console.log("YEAR="+selectedYear+", ["+digit_3.currentIndex+","+digit_2.currentIndex+","
                    +digit_1.currentIndex+","+digit_0.currentIndex+"]")
    }
    function yearDigit(year,index)
    {
        return ~~(year/Math.pow(10, index)) - ~~(year/Math.pow(10, index+1))*10
    }
    function calcYear()
    {
        return 1000*digit_3.currentValue + 100*digit_2.currentValue + 10*digit_1.currentValue + digit_0.currentValue
    }
    onOpened: selectedYear = 0

    property alias selectedHour: hour_digit.currentIndex
    property alias selectedMinute: minute_digit.currentIndex
    property alias selectedSecond: second_digit.currentIndex

    signal dateTimeAccepted

    contentItem: Page {
        header: ToolBar {
            TabBar {
                id: tabBar
                background: null
                anchors.centerIn: parent
                width: Math.min(implicitWidth, parent.width)
                clip: true
                TabButton {
                    text: calcYear()+"."
                    width: implicitWidth
                }
                TabButton {
                    text: Qt.locale().monthName(selectedMonth, Locale.ShortFormat)
                    width: implicitWidth
                }
                TabButton {
                    text: selectedDay+"."
                    width: implicitWidth
                }
                TabButton {
                    text: ""+selectedHour+":"+~~(selectedMinute/10)+(selectedMinute%10)
                    width: implicitWidth
                }
            }
        }

        contentItem: SwipeView {
            currentIndex: tabBar.currentIndex
            interactive: false
            clip: true

            Page {
                clip: true
                Row {
                    id: yearDigits
                    anchors.centerIn: parent

                    DigitTumbler {
                        id: digit_3
                    }
                    DigitTumbler {
                        id: digit_2
                    }
                    DigitTumbler {
                        id: digit_1
                    }
                    DigitTumbler {
                        id: digit_0
                    }
                }
                Frame {
                    width: yearDigits.width
                    height: 30
                    anchors.centerIn: parent
                }
            }

            Page {
                id: monthPage
                clip: true
                GridView {
                    id: monthGrid
                    anchors.centerIn: parent
                    model: 12
                    readonly property int columnCount: monthPage.width / cellWidth
                    readonly property int rowCount: Math.min(monthPage.height / cellHeight, count / columnCount)
                    width: Math.min(cellWidth * columnCount, monthPage.width)
                    height: Math.min(cellHeight * rowCount, monthPage.height)
                    cellWidth: 150
                    cellHeight: 80
                    delegate: Item {
                        width: monthGrid.cellWidth
                        height: monthGrid.cellHeight
                        RoundButton {
                            radius: 5
                            checkable: true
                            checked: selectedMonth === index
                            width: monthGrid.cellWidth * 3 / 4
                            anchors.centerIn: parent
                            text: Qt.locale().monthName(index, Locale.LongFormat)
                            onClicked: selectedMonth = index
                        }
                    }
                }
            }

            Page {
                id: dayPage
                clip: true
                Flickable {
                    anchors.centerIn: parent
                    width: Math.min(daySelectorColumn.width, dayPage.width)
                    height: Math.min(daySelectorColumn.height, dayPage.height)
                    flickableDirection: Flickable.HorizontalAndVerticalFlick
                    contentWidth: daySelectorColumn.width
                    contentHeight: daySelectorColumn.height

                    Column {
                        id: daySelectorColumn
                        anchors.centerIn: parent
                        anchors.horizontalCenter: parent.horizontalCenter

                        DayOfWeekRow {
                            anchors {
                                left: daySelector.left
                                right: daySelector.right
                            }
                        }
                        MonthGrid {
                            id: daySelector
                            year: selectedYear
                            month: selectedMonth

                            delegate: RoundButton {
                                id: dayButton
                                checkable: true
                                checked: selectedMonth === model.month && selectedDay === model.day
                                opacity: model.month === selectedMonth ? 1.0 : 0.25
                                TextMetrics {
                                    id: textMetrics
                                    text: "30"
                                    font: dayButton.font
                                }
                                width: textMetrics.advanceWidth + leftPadding + rightPadding
                                radius: 5
                                text: model.day
                                onClicked: {
                                    selectedDay = model.day
                                    selectedYear = model.year
                                    selectedMonth = model.month
                                }
                            }
                        }
                    }
                }
            }

            Page {
                Row {
                    id: timeDigits
                    anchors.centerIn: parent
                    DigitTumbler {
                        id: hour_digit
                        base: 24
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: ":"
                    }
                    DigitTumblerLinked {
                        id: minute_digit
                        base: 60
                        circularLink: hour_digit
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: ":"
                    }
                    DigitTumblerLinked {
                        id: second_digit
                        base: 60
                        circularLink: minute_digit
                    }
                }
                Frame {
                    width: timeDigits.width
                    height: 30
                    anchors.centerIn: parent
                }
            }
        }

        footer: DialogButtonBox {
            id: buttons
            standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
            onRejected: close()
            onAccepted: {
                close()
                dateTimeAccepted()
            }
        }
    }
}
