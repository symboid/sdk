
import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.calendar 1.0

Popup {
    anchors.centerIn: parent

    width: Math.min(parent.width - 100, 700)
    height: Math.min(parent.height - 100, 500)

    property int selectedDay: 1
    readonly property string selectedDateStr: {
        var date = new Date(selectedYear, selectedMonth, selectedDay)
        return date.toLocaleDateString(Qt.locale())
    }
    property int selectedMonth: 0

    /*
    property int selectedYear_3: 2
    property int selectedYear_2: 0
    property int selectedYear_1: 1
    property int selectedYear_0: 4
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

    property int selectedYear: 1000*digit_3.currentIndex + 100*digit_2.currentIndex +
                               10*digit_1.currentIndex + digit_0.currentIndex
                               */
    property int selectedYear: 0
    onSelectedYearChanged: {
        var xx = selectedYear

        var digit_3_value = Math.floor(xx/1000)
        console.log(digit_3_value)
        digit_3.currentIndex = digit_3_value

        xx = xx - digit_3_value * 1000
//        console.log(xx+","+digit_3.currentIndex)
        var digit_2_value = Math.floor(xx/100)
        console.log(digit_2_value)
        digit_2.currentIndex = digit_2_value

        xx = xx - digit_2_value * 100
//        console.log(xx+","+digit_2.currentIndex)
        var digit_1_value = Math.floor(xx/10)
        console.log(digit_1_value)
        digit_1.currentIndex = digit_1_value

        xx = xx - digit_1_value * 10
//        console.log(xx+","+digit_1.currentIndex)
        digit_0.currentIndex = xx
        selectedYear = Qt.binding(function(){return 1000*digit_3.currentIndex + 100*digit_2.currentIndex +
                                             10*digit_1.currentIndex + digit_0.currentIndex})
    }

    function yearDigit(index)
    {
        return Math.floor(selectedYear/Math.pow(10, 3-index)) -
                Math.floor(selectedYear/Math.pow(10, 4-index))*10
    }

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
                clip: true
                interactive: false

                Item {
                    Row {
                        id: yearDigits
                        anchors.centerIn: parent
                        Tumbler {
                            id: digit_3
                            model: 10
//                            currentIndex: selectedYear_3
//                            onCurrentIndexChanged: selectedYear_3 = currentIndex
                        }
                        Tumbler {
                            id: digit_2
                            model: 10
//                            currentIndex: selectedYear_2
//                            onCurrentIndexChanged: selectedYear_2 = currentIndex
                        }
                        Tumbler {
                            id: digit_1
                            model: 10
//                            currentIndex: selectedYear_1
//                            onCurrentIndexChanged: selectedYear_1 = currentIndex
                        }
                        Tumbler {
                            id: digit_0
                            model: 10
//                            currentIndex: selectedYear_0
//                            onCurrentIndexChanged: selectedYear_0 = currentIndex
                        }
                    }
                    Frame {
                        width: yearDigits.width
                        height: 30
                        anchors.centerIn: parent
                    }

                }

                Item {
                    id: monthPage
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
                                opacity: checked ? 1.0 : 0.5
                                width: monthGrid.cellWidth * 3 / 4
                                anchors.centerIn: parent
                                text: Qt.locale().monthName(index, Locale.LongFormat)
                                onClicked: selectedMonth = index
                            }
                        }
                    }
                }

                Item {
                    Flickable {
                        anchors.centerIn: parent
                        Column {
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

                                delegate: Pane {
                                    id: dayPane
                                    readonly property bool isSelected: selectedMonth === model.month && selectedDay === model.day
                                    background: Rectangle {
                                        radius: 5
                                        color: dayPane.isSelected ? "lightgray" : "transparent"
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                selectedDay = model.day
                                                selectedYear = model.year
                                                selectedMonth = model.month
                                            }
                                        }
                                    }
                                    contentItem: Label {
                                        text: model.day
                                        horizontalAlignment: Label.AlignHCenter
                                        opacity: model.month === selectedMonth ? 1.0 : 0.25
                                        font.bold: dayPane.isSelected
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
            }
        }
    }
}
