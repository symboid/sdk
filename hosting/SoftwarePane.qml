
import QtQuick 2.12
import QtQuick.Controls 2.5
import Symboid.Sdk.Controls 1.0
import Symboid.Sdk.Hosting 1.0
import Symboid.Sdk.Network 1.0

FolderGroupFixed {
    title: qsTr("Software")
    FolderGroupExpanding {
        title: qsTr("About")
        FolderGroupLink {
            title: qsTr("Build information")
            folderPane: FolderPane {
                title: qsTr("Build information")
                FolderGroupFixed {
                    title: qsTr("Qt Framework")
                    FolderLabel {
                        title: qsTr("Version")
                        text: AppConfig.software.qt_version_string
                    }
                    FolderLabel {
                        title: qsTr("SSL support")
                        text: AppConfig.software.ssl_supported ? qsTr("Available") : qsTr("Not available")
                    }
                    FolderLabel {
                        title: qsTr("Runtime version of SSL Library")
                        text: AppConfig.software.ssl_lib_version_runtime
                        visible: AppConfig.software.ssl_supported
                    }
                    FolderLabel {
                        title: qsTr("Compile-time version of SSL Library")
                        text: AppConfig.software.ssl_lib_version_compiletime
                        visible: AppConfig.software.ssl_supported
                    }
                }

                FolderGroupFixed {
                    title: qsTr("Graphics information")
                    FolderLabel {
                        title: qsTr("API in use")
                        text: switch(GraphicsInfo.api) {
                              case GraphicsInfo.OpenGL: return "OpenGL / OpenGL ES"
                              case GraphicsInfo.Software: return qsTr("software")
                              case GraphicsInfo.Direct3D12: return "Direct3D 12"
                              case GraphicsInfo.Unknown: return qsTr("unknown")
                              default: return qsTr("other")
                              }
                    }
                    FolderLabel {
                        title: qsTr("API version")
                        text: GraphicsInfo.majorVersion + "." + GraphicsInfo.minorVersion
                    }
                }

                FolderGroupFixed {
                    title: qsTr("Components")
                    Repeater {
                        model: SoftwareUpdate.componentVersions
                        FolderItem {
                            mainItem: Column {
                                spacing: 10
                                Label {
                                    text: name
                                    font.bold: true
                                }
                                Label {
                                    readonly property string componentRepo: "https://github.com/symboid/" + name
                                    textFormat: Label.RichText
                                    text: '<a href="' + componentRepo + '">'  + componentRepo + '</a>'
                                    anchors.right: parent.right
                                    onLinkActivated: Qt.openUrlExternally(link)
                                }
                                Row {
                                    anchors.right: parent.right
                                    Pane {
                                        id: revidPane
                                        anchors.verticalCenter: parent.verticalCenter
                                        TextInput {
                                            id: revidText
                                            text: revid
                                            readOnly: true
                                            selectByMouse: true
                                            font.pointSize: 12
                                        }
                                    }
                                    Button {
                                        height: revidPane.height
                                        width: revidPane.height
                                        anchors.verticalCenter: parent.verticalCenter
                                        display: Button.IconOnly
                                        icon.source: "/icons/clipboard_copy_icon&24.png"
                                        onClicked: {
                                            revidText.selectAll()
                                            revidText.copy()
                                            revidText.deselect()
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    FolderGroupExpanding {
        title: qsTr("Update method")
        ButtonGroup {
            buttons: [ automatedSwUpdate.button, manualSwUpdate.button, noSwUpdate.button ]
        }
        SettingsRadioButton {
            id: automatedSwUpdate
            text: qsTr("Automated")
            enabled: false
            enumConfig: AppConfig.software.update_method_node
            enumValue: SoftwareConfig.UpdateAutomatic
            hint: qsTr("Download and integration of new software revision will be performed automatically. New features will be available after application relaunch.")
        }
        SettingsRadioButton {
            id: manualSwUpdate
            text: qsTr("Manual")
            enumConfig: AppConfig.software.update_method_node
            enumValue: SoftwareConfig.UpdateManual
            hint: qsTr("Software updates will be prompted and confirmed. New features and bugfixes are available after update process.")
        }
        SettingsRadioButton {
            id: noSwUpdate
            text: qsTr("Switched off")
            enumConfig: AppConfig.software.update_method_node
            enumValue: SoftwareConfig.UpdateNone
            hint: qsTr("No software updates will be executed at all. No new features and bugfixes are available.")
        }
    }
}
