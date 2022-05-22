import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

//Page {
//    header: TabBar {
//        id: dashboardTabBar
//        //        currentIndex: dashboardSwipeView.currentIndex

//        TabButton {
//            text: "Przeglad"
//            //            icon.source: "qrc:/history.svg"
//            //            display: AbstractButton.TextUnderIcon
//        }
//        TabButton {
//            text: "Przebieg imprezy"
//            //            icon.source: "qrc:/history.svg"
//            //            display: AbstractButton.TextUnderIcon
//        }
//    }

//    SwipeView {
//        id: dashboardSwipeView
//        interactive: false
//        anchors.fill: parent
//        currentIndex: dashboardTabBar.currentIndex
//    }
//}


Item {
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

        console.log("seconds since last " + diff_secs)

        if(diff_secs <= 60)
        {
            timeSinceLastDrinkTextField.text = "last consumed drink: < 1 minute ago"
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
                    }

//                    Text {
//                        id: shotsCounter
//                        anchors.horizontalCenter: parent.horizontalCenter
//                        text: partyController.ui_drinks_count
//                        font.pointSize: 50
//                    }
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
                        anchors.centerIn: parent
                        font.pixelSize: 10
                        text: "(" + index +") " + modelData.ui_name
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: drinkTypesList.currentIndex = index
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

                    dialog.openDialog(toastProvider.randomToast().ui_text)
                    partyController.addDrink()
                }

//                Column {
//                    anchors.centerIn: parent
//                    Text {
//                        text: "Add "
//                        anchors.horizontalCenter: parent.horizontalCenter
//                        font.pointSize: 20
//                    }

//                    Text {
//                        text: drinkController.ui_currentDrinkType
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }

//                    Text {
//                        text: drinkController.ui_currentDrinkAmountMl + "ml"
//                        anchors.horizontalCenter: parent.horizontalCenter
//                    }
//                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                //                width: parent.width
                //                height: 60
                spacing: 60

                Button {
                    id: partyButton
                    anchors.verticalCenter: parent.verticalCenter
                    height: 50
                    width: 200
                    text: masterController.ui_party_started ? "End party" : "Start party"
                    font.pointSize: 10
                    Material.background: Material.Purple
                    onClicked: {
                        //                        toolbar.labelText = shotsTaken
                        //                        drinkController.resetCounter()
                        if(masterController.ui_party_started) {
                            console.log("PartyDashboardView::endParty()")
                            masterController.endParty()
                            contentFrame.replace("qrc:DashboardView.qml")
                        }
                        else {
                            //                            shotsTaken = 0
                            masterController.startParty()
                            //                            drinkController.setPartyId(partyController.currentPartyId())
                        }
                    }
                }
            }
        }
    }
}
