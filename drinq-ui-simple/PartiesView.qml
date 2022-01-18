import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "yellow"

        Column {
            anchors.centerIn: parent
            spacing: 30

            ListView {
                //                    anchors.fill: parent
                id: partiesList
                height: 200
                width: parent.width
                anchors.margins: 20

                clip: true

                model: masterController.ui_parties

                delegate: partyPreviewDelegate
                spacing: 5

                focus: true
            }

            Component {
                id: partyPreviewDelegate

                Rectangle {
                    width: partiesList.width
                    height: 40

                    color: ListView.isCurrentItem?"#157efb" : "transparent"
                    border.color: Qt.lighter(color, 1.1)

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 10
                        text: "#" + index + " " + modelData.ui_name + " (start:" + modelData.ui_started + ")"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: partiesList.currentIndex = index
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
                    text: "Cancel"
                    font.pointSize: 10
                    Material.background: Material.Purple
                    onClicked: {
                        console.log("Cancel")
                        navigationController.goBack()
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
//                        drinkController.setCurrentDrinkProperties(drinkTypesList.currentIndex, amountInput.value)
                        navigationController.goBack()
//                        drinkController.setDrinkProperties(type, amount)
                    }
                }
            }
        }
    }
}
