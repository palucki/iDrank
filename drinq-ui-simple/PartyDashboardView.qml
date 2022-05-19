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
    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        LabelDialog {
            id: dialog
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
                    enabled: masterController.ui_party_started && partyController.ui_drinks_count > 0
                    onClicked: {
//                        console.log("Opening statistics view")
//                        contentFrame.pagesTitles.push(contentFrame.depth + " Statistics")
//                        contentFrame.push("qrc:PartySummaryView.qml")
                    }
                }
            }

            RoundButton {
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 200
                width: 200
                //                text: "Add"
                enabled: masterController.ui_party_started
                Material.background: Material.Orange

                //                icon: ""
                onClicked: {
                    dialog.openDialog(toastProvider.randomToast().ui_text)
                    partyController.addDrink()
                }

                Column {
                    anchors.centerIn: parent
                    Text {
                        text: "Add"
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pointSize: 20
                    }

                    Text {
                        text: drinkController.ui_currentDrinkType
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: drinkController.ui_currentDrinkAmountMl + "ml"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
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
