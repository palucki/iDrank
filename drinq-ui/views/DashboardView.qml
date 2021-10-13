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
        Panel {
            id: searchPanel
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                margins: Style.sizeScreenMargin
            }
            headerText: "Recent activity"
//            contentComponent:
//                StringEditorSingleLine {
//                stringDecorator: recentActivity.ui_searchText
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                }
//            }
        }

        ListView {
            id: itemsView
            anchors {
                top: searchPanel.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: Style.sizeScreenMargin
            }
            clip: true
            model: recentActivity.ui_recentActivity
            delegate:
                RecentActivityItemDelegate {
                    drink: modelData
                }
        }

    }

    CommandBar {
        commandList: masterController.ui_commandController.ui_dashboardViewContextCommands
    }
}

