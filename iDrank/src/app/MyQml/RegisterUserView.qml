import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "#142DC1"

        ColumnLayout {
            anchors.fill: parent
            spacing: 30

            TextField {
                Layout.margins: 50
                Layout.fillWidth: true
                Layout.maximumHeight: 60
                id: usernameInput
                color: "white"
                placeholderText: "Username"
                placeholderTextColor: "gray"
            }

            Button {
                Layout.fillWidth: true
                Layout.margins: 50
                Layout.maximumHeight: 60
                id: registerButton
                text: "Register"
                onClicked: {
                    if(usernameInput.text.trim().length > 0) {
                        users_controller.registerUser(usernameInput.text)
                    }
                }

                KeyNavigation.tab: registerButton
            }
        }
    }
}
