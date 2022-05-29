import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"
Page {
    Keys.onPressed: {
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace) {
            console.log("presed in dashboard view " + stackLayout.currentIndex)
            if(stackLayout.currentIndex == 0) {
                Qt.quit()
            }
            //else handled in PartyMasterView
        }
    }

    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: masterController.ui_party_started ? 1 : 0

        StartPartyView {
        }

        PartyMasterView {
        }
    }
}
