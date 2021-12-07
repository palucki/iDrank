import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import QtQuick.Layouts 1.12

import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: root

    width: 480
    height: 720
    visible: true
    title: qsTr("iDrunk")

    property int shotsTaken: 0

//    Material.theme: Material.Dark
//    Material.accent: Material.Purple

    Rectangle {
        anchors.fill: parent
        color: "skyblue"

        Column {
            anchors.centerIn: parent
            spacing: 30

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
                    text: shotsTaken
                    font.pointSize: 50
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "shots"
                }
            }

            RoundButton {
                id: addButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 100
                width: 100
                text: "Add"
                Material.background: Material.Orange

//                icon: ""
                onClicked: {
                    shotsTaken = shotsTaken + 1
                    drinkController.addDrink()
                }
            }

            RoundButton {
                id: resetButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: 50
                width: 50
                text: "Reset"
                font.pointSize: 5
                Material.background: Material.Purple
                onClicked: {
                    shotsTaken = 0
                    drinkController.resetCounter()
                }
            }

        }


    }

}
