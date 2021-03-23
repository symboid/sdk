
import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.calendar 1.0

Popup {
    anchors.centerIn: parent

    width: Math.min(parent.width - 50, 700)
    height: Math.min(parent.height - 50, 500)

    property int selectedDay: 1
    readonly property string selectedDateStr: {
        var date = new Date(selectedYear, selectedMonth, selectedDay)
        return date.toLocaleDateString(Qt.locale())
    }
    property int selectedMonth: 0

    property int selectedYear_3: 0
    property int selectedYear_2: 0
    property int selectedYear_1: 0
    property int selectedYear_0: 0
    property int selectedYear: 1000*selectedYear_3 + 100*selectedYear_2 + 10*selectedYear_1 + selectedYear_0
    onSelectedYearChanged: {
        var xx = selectedYear
        selectedYear_3 = Math.floor(xx/1000)
        xx = xx - selectedYear_3 * 1000
        selectedYear_2 = Math.floor(xx/100)
        xx = xx - selectedYear_2 * 100
        selectedYear_1 = Math.floor(xx/10)
        xx = xx - selectedYear_1 * 10
        selectedYear_0 = xx
        selectedYear = Qt.binding(function(){return 1000*selectedYear_3 + 100*selectedYear_2 + 10*selectedYear_1 + selectedYear_0})
    }

    function yearDigit(index)
    {
        return Math.floor(selectedYear/Math.pow(10, 3-index)) -
                Math.floor(selectedYear/Math.pow(10, 4-index))*10
    }

    signal dateTimeAccepted

    contentItem: Page {
        header: ToolBar {
            Label {
                anchors.centerIn: parent
                text: selectedDateStr
                font.italic: true
                font.bold: true
            }
        }

        contentItem: Item {
            TabBar {
                id: tabBar
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                TabButton {
                    text: qsTr("Year")
                }
                TabButton {
                    text: qsTr("Month")
                }
                TabButton {
                    text: qsTr("Day")
                }
            }
            SwipeView {
                anchors {
                    top: tabBar.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
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
                            model: 10
                            currentIndex: selectedYear_3
                            onCurrentIndexChanged: selectedYear_3 = currentIndex
                        }
                        DigitTumbler {
                            id: digit_2
                            circularLink: digit_3
                            currentIndex: selectedYear_2
                            onCurrentIndexChanged: selectedYear_2 = currentIndex
                        }
                        DigitTumbler {
                            id: digit_1
                            circularLink: digit_2
                            currentIndex: selectedYear_1
                            onCurrentIndexChanged: selectedYear_1 = currentIndex
                        }
                        DigitTumbler {
                            id: digit_0
                            circularLink: digit_1
                            currentIndex: selectedYear_0
                            onCurrentIndexChanged: selectedYear_0 = currentIndex
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
//                                background.opacity: checked ? 1.0 : 0.25
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
                        flickableDirection: Flickable.VerticalFlick | Flickable.HorizontalFlick
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
//                                    background.opacity: checked ? 1.0 : 0.0
//                                    background.opacity: checked ? 1.0 : 0.25
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
