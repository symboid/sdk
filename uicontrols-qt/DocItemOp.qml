
import QtQuick 2.12

Item {

    property string title: ""
    property Component control: null
    property bool canExec: false
    signal exec()
}
