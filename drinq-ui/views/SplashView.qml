import QtQuick 2.12

import assets 1.0

Item {
//    Rectangle {
//        anchors.fill: parent
//        color:  Style.colorBackground//"#f3c842"
//        Text {
//            anchors.centerIn: parent
//            text: "Splash View"
//        }
//    }

        Rectangle {
            anchors.fill: parent
            color: Style.colorDashboardBackground
            Image {
                id: logo
                source: "qrc:/assets/logo.png"
                anchors.verticalCenterOffset: 60
                anchors.horizontalCenterOffset: 0
                anchors.centerIn: parent
                width: Style.sizeDashboardLogo
                height: Style.sizeDashboardLogo
            }
            Text {
                anchors {
                    top: logo.bottom
                    horizontalCenter: logo.horizontalCenter
                }
                text: "Client Management System"
                color: Style.colorDashboardFont
                font.pixelSize: Style.pixelSizeDashboard
            }
        }
}
