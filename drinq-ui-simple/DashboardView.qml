import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        Popup {
            id: popup
            anchors.centerIn: parent
            height:parent.height
            width: parent.width
            contentItem: Text {
                text: "Content"
                MouseArea {
                    anchors.fill: parent
                    onClicked: popup.close()
                }
            }
            onOpened: {
                console.log("Selecting another toast")
            }
        }


        Column {
            anchors.centerIn: parent
            spacing: 30

            Rectangle {
                height: 150
                width: 200
                anchors.horizontalCenter: parent.horizontalCenter
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
                        text: partyController.ui_drinks_count
                        font.pointSize: 50
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "shots"
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: console.log("Opening statistics view")
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
                    //show toast Text
                    popup.open()

                    //get from drinkController
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
//                            shotsTaken = 0
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
                        contentFrame.push("qrc:DrinkPropertiesView.qml")
                    }
                }
            }
        }
    }
}
