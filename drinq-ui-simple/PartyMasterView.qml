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
                    color: "plum"
            }
            id: partyCenterLabel
            text: qsTr("Party title")
            //                maximumLength: 30
            color: "black"
            font.pointSize: 14
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        TabBar {
            background: Rectangle {
                    color: "plum"
            }

            Layout.fillWidth: true
            id: dashboardTabBar
            //        currentIndex: dashboardSwipeView.currentIndex

            TabButton {
                focusPolicy: Qt.NoFocus
                text: qsTr("Overview")
                //            icon.source: "qrc:/history.svg"
                //            display: AbstractButton.TextUnderIcon
            }
            TabButton {
                focusPolicy: Qt.NoFocus
                text: qsTr("Party statistics")
                enabled: partyController.ui_drinks_count > 0
                //            icon.source: "qrc:/history.svg"
                //            display: AbstractButton.TextUnderIcon
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
