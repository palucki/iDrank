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
            spacing: 30

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                source: "qrc:/logo_yellow.svg"
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("iDrank helps in tracking alcohol consumption.")
                color: "white"
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Remember to drink responsibly.")
                color: "white"
            }
        }
    }
}
