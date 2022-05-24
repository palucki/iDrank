import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "yellow"

        ListView {
                                anchors.fill: parent
            id: partiesList
//            height: 200
//            width: parent.width
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



                        historyCenterLabel.text = modelData.ui_name

                        console.log("Party id " + modelData.ui_id)

                        console.log("Size of drinks " + drinkProvider.getDrinksList(modelData.ui_id))

                        historyStackView.push("qrc:PartyStatisticsView.qml",
                                              {drinks: drinkProvider.getDrinksList(modelData.ui_id)})
                    }
                }
            }
        }
//        Column {
//            anchors.centerIn: parent
//            width: parent.width
//            spacing: 30
//        }
    }
}
