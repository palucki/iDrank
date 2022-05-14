import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "gray"

        Column {
            anchors.centerIn: parent
            spacing: 30

            Image {
                anchors.horizontalCenter: parent.horizontalCenter

                width: 200
                height: 200
                fillMode: Image.PreserveAspectFit
                source: "qrc:/logo.png"
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "iDrank"
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "iDrank"
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "iDrank"
            }


        }
    }
}
