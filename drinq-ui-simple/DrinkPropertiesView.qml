import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    property int shotsTaken: 0

    Rectangle {
        anchors.fill: parent
        color: "lightpink"

        Column {
            anchors.centerIn: parent
            spacing: 30

            ListView {
                //                    anchors.fill: parent
                id: drinkTypesList
                height: 200
                width: parent.width
                anchors.margins: 20

                clip: true

                model: drinkController.ui_drinkTypes

                delegate: drinkTypeDelegate
                spacing: 5

                focus: true
            }

            Component {
                id: drinkTypeDelegate

                Rectangle {
                    width: drinkTypesList.width
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

            Rectangle {
                width: drinkTypesList.width
                height: 40

                color: "orange"
                border.color: Qt.lighter(color, 1.1)

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 10
                    text: "(+) Add new"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked:
//                        drinkTypesList.currentIndex = index
                        console.log("Adding new drink type")
                }
            }

            SpinBox {
                anchors.horizontalCenter: parent.horizontalCenter
                id: amountInput
                width: 200
                height: 50
                stepSize: 10
                value: 50
                from: 0
                to: 1000
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
                    text: "Cancel"
                    font.pointSize: 10
                    Material.background: Material.Purple
                    onClicked: {
                        console.log("Cancel")
                        contentFrame.pop()
                    }
                }

                RoundButton {
                    id: typeButton
                    anchors.verticalCenter: parent.verticalCenter
                    height: 100
                    width: 100
                    text: "Ok"
                    font.pointSize: 10
                    Material.background: Material.LightGreen
                    onClicked: {
                        console.log("Ok")
                        drinkController.setCurrentDrinkProperties(drinkTypesList.currentIndex, amountInput.value)
                        contentFrame.pop()
//                        drinkController.setDrinkProperties(type, amount)
                    }
                }
            }
        }
    }
}
