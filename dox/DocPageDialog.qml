
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0

Popup {
    id: docPageDialog

    signal loadDocView(string viewName)
    signal switchDocPage(int viewIndex)

    property alias docPageCount: docPageView.docPageCount
    property alias fileMenuModel: docFileMenu.fileMenuModel
    property alias docMethodModel: docMethodView.docMethodModel

    TabBar {
        id: tabBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        TabButton {
            icon.source: "/icons/align_just_icon&32.png"
        }
        TabButton {
            icon.source: "/icons/calc_icon&32.png"
        }
        TabButton {
            icon.source: "/icons/doc_lines_stright_icon&32.png"
        }
        TabButton {
            icon.source: "/icons/bookmark_1_icon&32.png"
        }
    }
    HorizontalLine {
        id: horizontalLine
        anchors {
            top: tabBar.bottom
            left: parent.left
            right: parent.right
        }
    }

    SwitchView {
        currentIndex: tabBar.currentIndex
        anchors {
            top: horizontalLine.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        DocFileMenu {
            id: docFileMenu
            onFileMethodClicked: close()
        }
        DocMethodView {
            id: docMethodView
            onDocViewLoaded: close()
        }
        DocPageView {
            id: docPageView
            onSwitchDocPage: docPageDialog.switchDocPage(pageIndex)
            onDocPageLoaded: close()
        }
    }
}
