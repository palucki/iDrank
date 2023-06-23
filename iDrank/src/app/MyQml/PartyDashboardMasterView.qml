import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Page {
    focus: true
    Keys.onPressed: {
        console.log("Pressed in PartyDashboardMasterView depth " + partyDashboardStackView.depth)
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace) {
            if(partyDashboardStackView.depth >= 2) {
                console.log("Executing pop")
                partyDashboardStackView.pop()
                event.accepted = true
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        LabelDialog {
            id: dialog
        }

        StackView {
            id: partyDashboardStackView

            anchors.fill: parent
            clip: true

            initialItem: PartyDashboardView {}
        }

    }
}
