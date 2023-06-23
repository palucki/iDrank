import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"

        ListView {
            anchors.fill: parent
            id: partiesList
            anchors.margins: 20

            clip: true
            model: masterController.ui_parties

            delegate: partyPreviewDelegate
            spacing: 5

            focus: false
        }

        Component {
            id: partyPreviewDelegate

            Rectangle {
                width: partiesList.width
                height: 40
                border.color: Qt.lighter(color, 1.1)

                function partyDecoration(partyId, currentPartyId) {
                    if(currentPartyId === partyId)
                        return ">>> "

                    return ""
                }

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 10
                    text: partyDecoration(modelData.ui_id, partyController.ui_current_party_id)
                    + modelData.ui_name + " (start:" + modelData.ui_started + ")"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Clicked on party " + modelData.ui_name)
//                        partiesList.currentIndex = index
                        historyCenterLabel.text = modelData.ui_name
                        console.log("Party id " + modelData.ui_id)
                        console.log("Size of drinks " + drinkProvider.getUIDrinksList(modelData.ui_id))
                        historyStackView.push("PartyStatisticsView.qml",
                                              {partyId: modelData.ui_id,
                                               drinks: drinkProvider.getUIDrinksList(modelData.ui_id),
                                               partyStarted: modelData.ui_started,
                                               partyEnded: modelData.ui_ended})
                    }
                }
            }
        }
    }
}
