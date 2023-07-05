import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
import Qt5Compat.GraphicalEffects

import "qrc:/js/common.js" as CommonJs

Page {
    Timer {
        id: timeSinceLastDrinkCounter
        interval: 10000; running: true; repeat: true
        onTriggered: {
            updateTimeSinceLastDrink()
        }
    }

    Component.onCompleted : {
        updateTimeSinceLastDrink()

        amountInput.value = drink_type_controller.ui_current_drink_amount_ml
    }

    // Connections {
    //     target: partyController
    //     function onUi_drinksChanged(){  updateTimeSinceLastDrink() }
    // }

    function updateTimeSinceLastDrink() {
        var diff_secs = party_controller.secondsSinceLastDrink()
        timeSinceLastDrinkTextField.text = CommonJs.updateTimeSinceLastDrink(diff_secs)
    }

    Rectangle {
        anchors.fill: parent
        //        color: "skyblue"

        LabelDialog {
            id: dialog
        }

        ConfirmationDialog {
            id: endPartyconfirmationDialog
            standardButtons: Dialog.Ok | Dialog.Cancel
            onAccepted: party_controller.endParty()
        }

        Column {
            anchors.centerIn: parent
            spacing: 10

            Rectangle {
                height: 150
                width: 200
                anchors.horizontalCenter: parent.horizontalCenter
                Column {
                    spacing: 5
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("Currently after:")
                    }

                    Text {
                        id: shotsCounter
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: party_controller.ui_drinks_count
                        font.pointSize: 50
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("shots")
                    }
                }
            }

            Rectangle {
                height: 50
                width: 200
                anchors.horizontalCenter: parent.horizontalCenter
                Column {
                    spacing: 5
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: timeSinceLastDrinkTextField
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "PLACEHOLDER FOR TIME SINCE LAST DRINK"
                        wrapMode: Text.WordWrap
                        width: 200
                    }
                }
            }

            ListView {
                //                    anchors.fill: parent
                id: drinkTypesList
                height: 50
                width: parent.width
                anchors.margins: 20

                clip: true
                orientation: ListView.Horizontal

                model: drink_type_controller.ui_drink_types

                delegate: drinkTypeDelegate
                spacing: 5

                onCurrentIndexChanged: {
                    amountInput.value = drink_type_controller.ui_drink_types[currentIndex].ui_default_amount_ml
                }

                footer:
                    Rectangle {
                    width: 40 //drinkTypesList.width
                    height: 40
                    color: "transparent"

                    RoundButton {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Will add new drink type")
                            partyDashboardStackView.push("DrinkPropertiesView.qml")
                        }
                        text: "+"
                        Material.background: "transparent"
                    }
                }
            }

            Component {
                id: drinkTypeDelegate

                Rectangle {
                    width: 40 //drinkTypesList.width
                    height: 40

                    color: ListView.isCurrentItem ? "#F6B500" : "transparent"
                    border.color: Qt.lighter(color, 1.1)

                    Text {
                        id: textItem
                        anchors.centerIn: parent
                        font.pixelSize: 10
                        text: modelData.ui_name
                        wrapMode: Text.WordWrap
                        width: parent.width
                        clip: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            drinkTypesList.currentIndex = index
                        }
                        onDoubleClicked: {
                            console.log("editing index " + index)
                            partyDashboardStackView.push("DrinkPropertiesView.qml",
                                                         {drinkType: drink_type_controller.ui_drink_types[index],
                                                          drink_index: index})
                        }
                    }
                }
            }

            Label {
                text: qsTr("amount (ml)")
            }

            SpinBox {
                id: amountInput
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                height: 50
                stepSize: 10
                from: 0
                to: 1000
                editable: true
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                RoundButton {
                    focusPolicy: Qt.NoFocus
                    id: addButton
//                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 50
                    width: 175
                    Material.foreground: "white"
                    Material.background: "#ED690F"
                    radius: 10
                    text: qsTr("Add")
                    enabled: party_controller.ui_party_started && involved_users_controller.ui_involved_users.length > 0
                    onClicked: {
                        drink_type_controller.setCurrentDrinkType(drinkTypesList.currentIndex)
                        drink_type_controller.setCurrentDrinkAmountMl(amountInput.value)
                        
                        // var toast = toastProvider.randomToast(partyController.ui_current_party_id)
                        // dialog.openDialog(toast.ui_text)

                        party_controller.addDrink(toast.id, involved_users_controller.ui_involved_users)
                    }
                }

                RoundButton {
                    focusPolicy: Qt.NoFocus
                    id: playersButton
                    height: 50
                    width: 75
                    Material.foreground: "orange"
                    Material.background: "white"
                    radius: 10
                    text: involved_users_controller.ui_involved_users.length
                    icon.source: "qrc:/img/users.png"
                    font.pointSize: 10
                    onClicked: {
                        console.log("Clicked on players")
                        partyDashboardStackView.push("PlayersView.qml",
                                                     {users: users_controller.getUsers()})
                    }
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 60

                RoundButton {
                    focusPolicy: Qt.NoFocus
                    id: partyButton
                    anchors.verticalCenter: parent.verticalCenter
                    height: 50
                    width: 250
                    Material.foreground: "gray"
                    Material.background: "white"
                    radius: 10
                    text: party_controller.ui_party_started ? qsTr("End party") : qsTr("Start party")
                    font.pointSize: 10
                    onClicked: {
                        if(party_controller.ui_party_started) {
                            console.log("PartyDashboardView::endParty()")
                            endPartyconfirmationDialog.openDialog(qsTr("Do you want to end the party?"))
                        }
                        else {
                            party_controller.startParty()
                        }
                    }
                }
            }
        }
    }
}
