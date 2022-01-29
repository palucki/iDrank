import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

Item {
    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        Column {
            anchors.centerIn: parent
            spacing: 30

            CustomDialog {
                id: dialog
                dialogTitle: "Starting new party..."
                dialogPlaceholderText: "Give it a title"

                onAccepted: {
                    console.log("Party name " + dialogText)
                    partyController.startParty(dialogText)
                    pagesTitles[0] = dialogText
                    contentFrame.replace("qrc:PartyDashboardView.qml")
                }
            }

            RoundButton {
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 200
                width: 200
                text: "Start"
                Material.background: Material.Orange
                onClicked: dialog.openDialog()
            }

            //            Row {
            //                anchors.horizontalCenter: parent.horizontalCenter
            //                //                width: parent.width
            //                //                height: 60
            //                spacing: 60

            //                RoundButton {
            //                    id: partyButton
            //                    anchors.verticalCenter: parent.verticalCenter
            //                    height: 100
            //                    width: 100
            //                    enabled: partyController.ui_party_started
            //                    text: partyController.ui_party_started ? "End party" : "Start party"
            //                    font.pointSize: 10
            //                    Material.background: Material.Purple
            //                    onClicked: {
            //                        //                        toolbar.labelText = shotsTaken
            //                        //                        drinkController.resetCounter()
            //                        if(partyController.ui_party_started) {
            //                            partyController.endParty()
            //                        }
            //                        else {
            ////                            shotsTaken = 0
            //                            partyController.startParty()
            ////                            drinkController.setPartyId(partyController.currentPartyId())
            //                        }
            //                    }
            //                }

            //                RoundButton {
            //                    id: typeButton
            //                    anchors.verticalCenter: parent.verticalCenter
            //                    height: 100
            //                    width: 100
            //                    text: "Drink type"
            //                    font.pointSize: 10
            //                    Material.background: Material.LightGreen
            //                    onClicked: {
            //                        console.log("Select drink type")
            //                        contentFrame.pagesTitles.push(contentFrame.depth + " Drink properties")
            //                        contentFrame.push("qrc:DrinkPropertiesView.qml")
            //                    }
            //                }
            //            }
        }
    }
}
