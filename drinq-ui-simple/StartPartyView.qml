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

            TextFieldDialog {
                id: dialog
                dialogTitle: "Starting new party..."
                dialogPlaceholderText: "Give it a title"

                onAccepted: {
                    console.log("Party name " + dialogText)
                    masterController.startParty(dialogText)
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
        }
    }
}
