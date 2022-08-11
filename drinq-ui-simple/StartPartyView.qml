import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

Page {
    function updateTimeSinceLastDrink() {
        var diff_secs = masterController.secondsSinceLastDrink()

        if(diff_secs === -1)
        {
            timeSinceLastDrinkTextField.text = ""
        }
        else if(diff_secs <= 60)
        {
            timeSinceLastDrinkTextField.text = qsTr("last consumed drink: less than a minute ago")
        }
        else if(diff_secs <= 3600)
        {
            var diff_mins = diff_secs / 60
            timeSinceLastDrinkTextField.text = qsTr("last consumed drink: ") + parseInt(diff_mins) + qsTr(" minutes ago")
        }
        else
        {
            var diff_hours = diff_secs / 3600
            timeSinceLastDrinkTextField.text = qsTr("last consumed drink: ") + parseInt(diff_hours) + qsTr(" hour ago")
        }
    }

    Timer {
        id: timeSinceLastPartyCounter
        interval: 60000; running: true; repeat: true
        onTriggered: {
            updateTimeSinceLastDrink()
        }
    }

    Component.onCompleted : {
        updateTimeSinceLastDrink()
    }

    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        Column {
            anchors.centerIn: parent
            spacing: 30

            TextFieldDialog {
                id: dialog
                dialogTitle: qsTr("Starting new party...")
                dialogPlaceholderText: qsTr("Give it a title")

                onAccepted: {
                    console.log("Party name " + dialogText)
                    masterController.startParty(dialogText)
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

            RoundButton {
                focusPolicy: Qt.NoFocus
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 200
                width: 200
                text: qsTr("Start")
                Material.background: Material.Orange
                onClicked: dialog.openDialog()
            }
        }
    }
}
