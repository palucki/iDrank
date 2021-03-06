import QtQuick 2.12
import QtQuick.Controls 2.12

import DrinQ 1.0
import assets 1.0
import components 1.0

Item {
//    property Client newClient: masterController.ui_newClient
    property Party selectedParty

    Component.onCompleted:  {
//        if(!selectedParty) {
//            console.log("Party was not set, selecting newparty")
//            selectedParty = masterController.ui_newParty
//        }

        masterController.ui_commandController.setSelectedParty(selectedParty)
    }

    Rectangle {
        anchors.fill: parent
        color: Style.colorBackground
    }

    ScrollView {
        id: scrollView
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: commandBar.top
            margins: Style.sizeScreenMargin
        }
        clip: true

        Column {
            spacing: Style.sizeScreenMargin
            width: scrollView.width
            Panel {
                headerText: "Party Details"
                contentComponent:
                    Column {
                    spacing: Style.sizeControlSpacing
                    StringEditorSingleLine {
                        stringDecorator: selectedParty ? selectedParty.ui_title : null
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                    }
                    StringEditorSingleLine {
                        stringDecorator: selectedParty ? selectedParty.ui_notes : null
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                    }
                }
            }
            DrinksEditor {
                width: scrollView.width
                party: selectedParty
                headerText: "Consumed drinks"
            }
        }
    }
    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_editPartyViewContextCommands
    }
}

