
import QtQuick 2.12
import QtQuick.Controls 2.5

Page {

    property MessagePopup infoPopup: MessagePopup {
        iconSource: "/icons/info_icon&32.png"
        iconColor: "green"
        autoClose: true
    }

    property MessagePopup warningPopup: MessagePopup {
        iconSource: "/icons/attention_icon&32.png"
        iconColor: "orange"
    }

    property MessagePopup errorPopup: MessagePopup {
        iconSource: "/icons/round_delete_icon&32.png"
        iconColor: "red"
    }

    property MessagePopup busyPopup: MessagePopup {
        messageIndicator: BusyIndicator {
            running: true
        }
    }
}
