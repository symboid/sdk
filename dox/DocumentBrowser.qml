
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

StackView {
    id: documentBrowser

    readonly property int docPageCount: depth + forwardStack.depth
    property int docPageIndex: 0

    property alias initialPage: documentBrowser.initialItem

    pushEnter: null
    pushExit: null
    popEnter: null
    popExit: null

    StackObject {
        id: forwardStack
    }

    function backward()
    {
        forwardStack.push(pop())
        --docPageIndex
    }
    function forward()
    {
        push(forwardStack.pop())
        ++docPageIndex
    }
    property var createDocPage: function(viewName)
    {
        var screenComponent = Qt.createComponent(viewName)
        return screenComponent.createObject(this)
    }
    function newDocPage(viewName)
    {
        var screen = createDocPage(viewName)
        forwardStack.cleanup()
        push(screen)
        docPageIndex++
        return screen
    }
    function switchDocPage(pageIndex)
    {
        while (depth < pageIndex + 1)
        {
            push(forwardStack.pop())
        }
        while (depth > pageIndex + 1)
        {
            forwardStack.push(pop())
        }
        docPageIndex = pageIndex
    }

    property var closeDocPage: function(docPage)
    {
    }
    Connections {
        target: currentItem
        function onCloseView()
        {
            closeDocPage(currentItem)
            if (depth > 1)
            {
                pop()
                docPageIndex--
            }
            else if (forwardStack.depth > 0)
            {
                replace(currentItem, forwardStack.pop())
            }
        }
    }

    property alias docMethodModel: docPageDialog.docMethodModel
    function docPageDialogOpen()
    {
        docPageDialog.open()
    }
    DocPageDialog {
        id: docPageDialog
        anchors.centerIn: parent
        width: Math.min(400, parent.width - 50)
        height: parent.height - 2 * 50

        docPageCount: parent.docPageCount

        onLoadDocView: newDocPage(viewName)
        onSwitchDocPage: parent.switchDocPage(viewIndex)
    }
}
