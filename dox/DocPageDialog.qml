
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Popup {
    id: docPageDialog

    signal loadDocView(string viewName)
    signal switchDocPage(int viewIndex)

    onLoadDocView: close()
    onSwitchDocPage: close()

    property alias docPageCount: docPageView.docPageCount
    property alias docMethodModel: docMethodView.docMethodModel

    TabBar {
        id: tabBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        TabButton {
            icon.source: "/icons/calc_icon&32.png"
        }
        TabButton {
            icon.source: "/icons/doc_lines_icon&32.png"
        }
    }

    SwitchView {
        currentIndex: tabBar.currentIndex
        anchors {
            top: tabBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        DocMethodView {
            id: docMethodView
            onLoadDocView: docPageDialog.loadDocView(viewName)
        }
        DocPageView {
            id: docPageView
            onSwitchDocPage: docPageDialog.switchDocPage(pageIndex)
        }
    }
}
