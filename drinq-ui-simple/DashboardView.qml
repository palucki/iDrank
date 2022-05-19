import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

Item {
    StackLayout {
        id: layout
        anchors.fill: parent

        currentIndex: masterController.ui_party_started ? 1 : 0

        StartPartyView {

        }

        PartyMasterView {

        }
    }
}
