import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import QtQuick.Layouts 1.12

import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: root

    onActiveFocusItemChanged: print("activeFocusItem", activeFocusItem)

    width: 480
    height: 720
    visible: true
    title: qsTr("iDrank")

    Item {
        id: navigationController
        signal goBack
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        interactive: false
        currentIndex: masterTabBar.currentIndex

        focus: true //required to allow capture of buttons
        Keys.onPressed: {
            console.log("pressed in MasterView")
            if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace) {
                if(masterTabBar.currentIndex == 0) { // start party / party dashboard
                    //ignore, handle in dashboard view
                    console.log("--> handled in DashboardView")
                } else if(masterTabBar.currentIndex == 1) { // history master view
                    //ignore, handle in history master view
                    console.log("--> handed in HistoryMasterView")
                } else if(masterTabBar.currentIndex == 2) { //about
                    masterTabBar.currentIndex = 0
                    event.accepted = true
                }
            }
        }

        DashboardView {
            id: dashboardView
        }

        HistoryMasterView {
            id: historyView
        }

        AboutView {
            id: aboutView
        }
    }

    footer: TabBar {
        id: masterTabBar

        TabButton {
            focusPolicy: Qt.NoFocus
            text: qsTr("Current party")
            icon.source: "qrc:/img/home.png"
            display: AbstractButton.TextUnderIcon
        }
        TabButton {
            focusPolicy: Qt.NoFocus
            text: qsTr("History")
            icon.source: "qrc:/img/history_icon_grey.svg"
            display: AbstractButton.TextUnderIcon
        }
        TabButton {
            focusPolicy: Qt.NoFocus
            text: qsTr("About")
            icon.source: "qrc:/img/info.png"
            display: AbstractButton.TextUnderIcon
        }
    }
}
