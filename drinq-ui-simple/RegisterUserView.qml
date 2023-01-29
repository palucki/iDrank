import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "#142DC1"

        Column {
            anchors.centerIn: parent
//            anchors.alignWhenCentered: true
//            width: 360 * scaleFactor
//            spacing: 14 * intScaleFactor
            spacing: 30

            TextField {
                id: usernameInput
                color: "white"
                onAccepted: emailInput.forceActiveFocus()
                placeholderText: "Username"
                placeholderTextColor: "gray"
                KeyNavigation.tab: emailInput
            }

            TextField {
                id: emailInput

                color: "white"
                placeholderText: "Email"
                placeholderTextColor: "gray"
                KeyNavigation.tab: registerButton
            }

            Button {
                id: registerButton
                text: "Register"
                onClicked: {
                    masterController.registerUser(usernameInput.text, emailInput.text)
                }

                KeyNavigation.tab: registerButton
            }
        }
    }
}
