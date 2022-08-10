import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

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

        console.log("Setting values from settings. Drink type " + drinkController.ui_currentDrinkTypeIndex
                    + " amount " + drinkController.ui_currentDrinkAmountMl)
        drinkTypesList.currentIndex = drinkController.ui_currentDrinkTypeIndex
        amountInput.value = drinkController.ui_currentDrinkAmountMl
    }


    Connections {
        target: partyController
        function onUi_drinksChanged(){  updateTimeSinceLastDrink() }
    }

    function updateTimeSinceLastDrink() {
        var diff_secs = partyController.secondsSinceLastDrink()

        if(diff_secs === -1)
        {
            timeSinceLastDrinkTextField.text = ""
        }
        else if(diff_secs <= 60)
        {
            timeSinceLastDrinkTextField.text = "last consumed drink: less than a minute ago"
        }
        else if(diff_secs <= 3600)
        {
            var diff_mins = diff_secs / 60
            timeSinceLastDrinkTextField.text = "last consumed drink: " + parseInt(diff_mins) + " minutes ago"
        }
        else
        {
            var diff_hours = diff_secs / 3600
            timeSinceLastDrinkTextField.text = "last consumed drink: " + parseInt(diff_hours) + " hour ago"
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        LabelDialog {
            id: dialog
        }

        ConfirmationDialog {
            id: endPartyconfirmationDialog
            onAccepted: masterController.endParty()
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
                    enabled: masterController.ui_party_started && partyController.ui_drinks_count > 0
                    onClicked: {
//                        console.log("Opening statistics view")
//                        contentFrame.pagesTitles.push(contentFrame.depth + " Statistics")
//                        contentFrame.push("qrc:PartyStatisticsView.qml")
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
                        text: "PLACEHOLDER"
                        wrapMode: Text.WordWrap
                        width: 200
                    }
                }
            }

            Label {
                text: "wybierz rodzaj alkoholu"
            }

            ListView {
                //                    anchors.fill: parent
                id: drinkTypesList
                height: 50
                width: parent.width
                anchors.margins: 20

                clip: true
                orientation: ListView.Horizontal

                model: drinkController.ui_drinkTypes

                delegate: drinkTypeDelegate
                spacing: 5

                footer:
                    Rectangle {
                        width: 40 //drinkTypesList.width
                        height: 40
                        color: "transparent"

                        Text {
                            id: textItem
                            anchors.centerIn: parent
                            font.pixelSize: 10
                            text: "( Add new )"
                            wrapMode: Text.WordWrap
                            width: parent.width
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("Will add new drink type")
                                partyDashboardStackView.push("qrc:DrinkPropertiesView.qml")
                            }
                        }
                    }
//                focus: true
            }

            Component {
                id: drinkTypeDelegate

                Rectangle {
                    width: 40 //drinkTypesList.width
                    height: 40

                    color: ListView.isCurrentItem?"#157efb" : "transparent"
                    border.color: Qt.lighter(color, 1.1)

                    Text {
                        id: textItem
                        anchors.centerIn: parent
                        font.pixelSize: 10
                        text: "(" + index +") " + modelData.ui_name
                        wrapMode: Text.WordWrap
                        width: parent.width
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            drinkTypesList.currentIndex = index
                            amountInput.value = drinkController.ui_drinkTypes[index].ui_default_amount_ml
                        }
                        onDoubleClicked: {
                            console.log("editing index " + index)
                            partyDashboardStackView.push("qrc:DrinkPropertiesView.qml",
                                                         {drinkType: drinkController.ui_drinkTypes[index]})
                        }
                    }
                }
            }

            Label {
                text: "ilość (ml)"
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


            Button {
                focusPolicy: Qt.NoFocus
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 50
                width: 200
                text: "Add"
                enabled: masterController.ui_party_started
                Material.background: Material.Orange

                //                icon: ""
                onClicked: {
                    drinkController.setCurrentDrinkProperties(drinkTypesList.currentIndex, amountInput.value)

                    var toast = toastProvider.randomToast(partyController.ui_current_party_id)
                    dialog.openDialog(toast.ui_text)
                    partyController.addDrink(toast.id)
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 60

                Button {
                    focusPolicy: Qt.NoFocus
                    id: partyButton
                    anchors.verticalCenter: parent.verticalCenter
                    height: 50
                    width: 200
                    text: masterController.ui_party_started ? "End party" : "Start party"
                    font.pointSize: 10
                    Material.background: Material.Purple
                    onClicked: {
                        if(masterController.ui_party_started) {
                            console.log("PartyDashboardView::endParty()")
                            endPartyconfirmationDialog.openDialog("Czy na pewno zakończyć imprezę?")
                        }
                        else {
                            masterController.startParty()
                        }
                    }
                }
            }
        }
    }
}
