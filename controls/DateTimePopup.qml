
import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.calendar 1.0

Popup {
    anchors.centerIn: parent

    width: Math.min(parent.width - 100, 700)
    height: Math.min(parent.height - 100, 500)

    property int selectedDay: 1
    readonly property string selectedDateStr: {
        var date = new Date(daySelector.year, selectedMonth, selectedDay)
        return date.toLocaleDateString(Qt.locale())
    }
    property int selectedMonth: 0
    property int selectedYear: 1234

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
//                    anchors.fill: parent
                    Row {
                        id: yearDigits
                        anchors.centerIn: parent
                        Repeater {
                            model: 4
                            delegate: Tumbler {
                                model: 10
                                currentIndex: yearDigit(index)
                                onCurrentIndexChanged: {
                                    var upper = Math.floor(selectedYear / Math.pow(10, 4-index)) * Math.pow(10, 4-index)
                                    var lower = selectedYear - Math.floor(selectedYear / Math.pow(10, 3-index)) * Math.pow(10, 3-index)
//                                    selectedYear = upper + Math.pow(10, 4-index) * currentIndex + lower
                                    console.log("upper="+upper+", lower="+lower+")
                                }
                            }
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

                Flickable {
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
                                            daySelector.year = model.year
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
