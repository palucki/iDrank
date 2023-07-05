import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

Item {
    property var users;
    property var involved_users : involved_users_controller.ui_involved_users

    TextFieldDialog {
        id: dialog
        dialogTitle: qsTr("Adding new player...")
        dialogPlaceholderText: qsTr("Player's name")

        onAccepted: {
            console.log("New player " + dialogText)

            if(dialogText.trim() === '')
            {
                console.log("Empty name given!")
                return;
            }

            if(users.includes(dialogText))
            {
                console.log("User already exists")
                return;
            }

            users_controller.registerUser(dialogText)
            users = users_controller.getUsers(true)
        }
    }

    ConfirmationDialog {
        id: deleteUserConfirmationDialog
        standardButtons: Dialog.Ok | Dialog.Cancel
    }

    Rectangle {
        anchors.fill: parent

        ListView {
            width: parent.width
            height: parent.height

            model: users
            delegate: playerDelegate

            footer:
                Rectangle {

                visible: users.length < 3

                width: parent.width
                height: 40
                color: "transparent"

                RoundButton {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Will add new player")
                        onClicked: dialog.openDialog()
                    }
                    text: "Add new player"
                    Material.background: "transparent"
                }
            }

        }
    }

    Component.onDestruction: {
        console.log("Destorying");
        var involved = []
        for(var i = 0; i < users.length; ++i)
        {
            if(users[i].ui_involved)
            {
                console.log("Id: " + users[i].ui_id + " involved")
                involved.push(users[i].ui_id)
            }
        }

        masterController.setInvolvedUsers(involved)
    }

    Component {
        id: playerDelegate

        Rectangle {
            width: 200
            height: 40

            CheckBox {
                id: playerInvolvedCheckbox
                checked: modelData.ui_involved
                onToggled: {
                    modelData.ui_involved = checked
                    console.log("Toggling for " + modelData.ui_id + " " + modelData.ui_involved)
                }
            }

            Label {
                anchors.left: playerInvolvedCheckbox.right
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 20
                text: modelData.ui_name
            }

            Button {
                visible: modelData.ui_id != 1

                focusPolicy: Qt.NoFocus
                anchors.right: parent.right
                text: "X"
                onClicked: {
                    deleteUserConfirmationDialog.openDialog(qsTr("Delete the user?"))
                    deleteUserConfirmationDialog.accepted.connect(function(){
                        console.log("DELETE user")
                        users_controller.deleteUser(modelData.ui_id)
                        users = users_controller.getUsers(true)
                    })
                }
            }
        }
    }

}
