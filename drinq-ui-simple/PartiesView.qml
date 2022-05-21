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
            width: parent.width
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

                focus: false
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
                        onClicked: {
                            console.log("Clicked on party " + modelData.ui_name)
                            partiesList.currentIndex = index

                            historyStackView.push("qrc:PartyStatisticsView.qml")
                        }
                    }
                }
            }
        }
    }
}
