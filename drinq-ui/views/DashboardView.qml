import QtQuick 2.12
import QtQuick.Controls 2.12

import DrinQ 1.0
import components 1.0
import assets 1.0

Item {
    property RecentActivity recentActivity: masterController.ui_recentActivity

    Component.onCompleted: {
        masterController.ui_commandController.onDashboardLoadExecuted()
    }

    Rectangle {
        anchors.fill: parent
        color: Style.colorBackground
    }

    Column {
//        height: parent.height
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: commandBar.top
//            margins: Style.sizeScreenMargin
        }

        Panel {
            id: searchPanel
            anchors {
                left: parent.left
                right: parent.right
                margins: Style.sizeScreenMargin
            }
            headerText: "Recent activity"
        }

        ListView {
            id: itemsView
            height: parent.height - commandBar.height
            anchors {
//                top: searchPanel.bottom
                left: parent.left
                right: parent.right
//                bottom: parent.bottom
                margins: Style.sizeScreenMargin
            }
            clip: true
            model: recentActivity.ui_recentActivity
            delegate:
                RecentActivityItemDelegate {
                    party: modelData
                }
        }
    }



//    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_dashboardViewContextCommands
//        anchors.bottom: parent.bottom
    }
}

