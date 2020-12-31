
import QtQuick 2.12
import QtQuick.Controls 2.5

ToolBar {
    id: toolbar
    property alias toolModel: toolButtons.model
    property LoadListView listView: null
    property int textInputIndex: -1
    property alias textInput: textInputItem.itemTitle
    signal textInputClicked()

    function textInputShow(show)
    {
        toolButtons.itemAt(textInputIndex).checked = show
        if (!show)
        {
            textInputIndex = -1
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater {
                id: toolButtons
                delegate: ToolButton {
                    icon.source: iconSource
                    checkable: withTextInput
                    enabled: !withTextInput || textInputIndex == -1 || textInputIndex == index
                    onCheckedChanged: {
                        if (checked)
                        {
                            textInputIndex = index
                            listView.currentIndex = -1
                            textInputItem.setEditFocus()
                        }
                        else
                        {
                            textInputIndex = -1
                        }
                    }
                    onClicked: toolAction()
                }
            }
        }
        LoadListItem {
            id: textInputItem
            visible: textInputIndex !== -1
            anchors.horizontalCenter: parent.horizontalCenter
            width: toolbar.width
            itemWidth: rowWidth
            loadIconSource: textInputIndex !== -1 ? toolModel.get(textInputIndex).iconSource : ""
            selectorVisible: false
            lineColor: toolbar.background.color
            onEditAccepted: textInputClicked()
            onEditCanceled: textInputShow(false)
            onButtonClicked: textInputClicked()
        }
    }
}
