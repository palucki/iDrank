import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/js/common.js" as CommonJs

Page {
    id: root
    function updateTimeSinceLastDrink() {
        var diff_secs = party_controller.secondsSinceLastDrink()
        timeSinceLastDrinkTextField.text = CommonJs.updateTimeSinceLastDrink(diff_secs)
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
        id: background
        anchors.fill: parent
        color: "#2039CB"

        ColumnLayout {
            anchors.fill: parent

            Text {
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                text: qsTr("Hello ") + users_controller.ui_admin_name
                color: "white"
                wrapMode: Text.WordWrap
            }

            Text {
                id: timeSinceLastDrinkTextField
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                text: "PLACEHOLDER SECONDS SINCE LAST DRINK"
                color: "white"
                wrapMode: Text.WordWrap
            }

            RoundButton {
                focusPolicy: Qt.NoFocus
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                Layout.minimumWidth: 150
                text: qsTr("Start")
                Material.foreground: "white"
                Material.background: "#ED690F"
                radius: 10
                onClicked: dialog.openDialog()
            }
            
            TextFieldDialog {
                id: dialog
                dialogTitle: qsTr("Starting new party...")
                dialogPlaceholderText: qsTr("Give it a title")

                onAccepted: {
                    console.log("Party name " + dialogText)
                    masterController.startParty(dialogText)
                }
            } 
        }
    }
}
