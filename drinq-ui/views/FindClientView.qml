import QtQuick 2.12

import assets 1.0
import DrinQ 1.0
import components 1.0

Item {
    property ClientSearch clientSearch: masterController.ui_clientSearch
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
            headerText: "Find Clients"
            contentComponent:
                StringEditorSingleLine {
                stringDecorator: clientSearch.ui_searchText
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
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
            model: clientSearch.ui_searchResults
            delegate:
                    SearchResultDelegate {
                        client: modelData
                    }
        }

    }

    CommandBar {
        commandList: masterController.ui_commandController.ui_findClientViewContextCommands
    }
}
