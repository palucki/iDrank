import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

Page {
    focus: true
    Keys.onPressed: {
        console.log("presed in partymasterview")
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace) {
            if(dashboardTabBar.currentIndex == 0) {
                Qt.quit()
            } else {
                dashboardTabBar.currentIndex = 0
                event.accepted = true
            }
        }
    }

    header: ColumnLayout {
        spacing: 0
        Label  {
            background: Rectangle {
                    color: "#142DC1"
            }
            id: partyCenterLabel
            text:  party_controller.ui_party_title
            color: "white"
            font.pointSize: 16
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        TabBar {
            background: Rectangle {
                color: "#142DC1"
            }

            Layout.fillWidth: true
            id: dashboardTabBar

            TabButton {
                focusPolicy: Qt.NoFocus
                text: qsTr("Overview")
                Material.foreground: "white"
                Material.accent: "white"
            }
            TabButton {
                focusPolicy: Qt.NoFocus
                text: qsTr("Party statistics")
                Material.foreground: "white"
                Material.accent: "white"
                enabled: party_controller.ui_drinks_count > 0
            }
        }
    }

    SwipeView {
        focus: true
        id: dashboardSwipeView
        interactive: false
        anchors.fill: parent
        currentIndex: dashboardTabBar.currentIndex

        PartyDashboardMasterView {
        }

        PartyStatisticsView {
        }
    }
}
