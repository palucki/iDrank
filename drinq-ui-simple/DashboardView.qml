import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

Item {
    property int shotsTaken: 0

    Rectangle {
        anchors.fill: parent
        color: "skyblue"
        Column {
            anchors.centerIn: parent
            spacing: 30

            Column {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Currently after:"
                }

                Text {
                    id: shotsCounter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: shotsTaken
                    font.pointSize: 50
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "shots"
                }
            }

            RoundButton {
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 200
                width: 200
                text: "Add"
                enabled: partyController.isPartyStarted()
                Material.background: Material.Orange

                //                icon: ""
                onClicked: {
                    shotsTaken = shotsTaken + 1
                    toolbar.labelText = shotsTaken
                    drinkController.addDrink()
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
//                width: parent.width
//                height: 60
                spacing: 60

                RoundButton {
                    id: partyButton
                    anchors.verticalCenter: parent.verticalCenter
                    height: 100
                    width: 100
                    text: partyController.isPartyStarted() ? "End party" : "Start party"
                    font.pointSize: 10
                    Material.background: Material.Purple
                    onClicked: {
//                        toolbar.labelText = shotsTaken
//                        drinkController.resetCounter()
                        if(partyController.isPartyStarted()) {
                            partyController.endParty()
                            text = "Start party"
                            addButton.enabled = false
                        }
                        else {
                            shotsTaken = 0
                            partyController.startParty()
                            drinkController.setPartyId(partyController.currentPartyId())
                            text = "End party"
                            addButton.enabled = true
                        }
                    }
                }

                RoundButton {
                    id: typeButton
                    anchors.verticalCenter: parent.verticalCenter
                    height: 100
                    width: 100
                    text: "Drink type"
                    font.pointSize: 10
                    Material.background: Material.LightGreen
                    onClicked: {
                        console.log("Select drink type")
                    }
                }
            }
        }
    }
}
