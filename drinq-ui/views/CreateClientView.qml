import QtQuick 2.12
import QtQuick.Controls 2.12

import DrinQ 1.0
import assets 1.0
import components 1.0

Item {
    property Client newClient: masterController.ui_newClient

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
                headerText: "Client Details"
                contentComponent:
                    Column {
                    spacing: Style.sizeControlSpacing
                    StringEditorSingleLine {
                        stringDecorator: newClient.ui_reference
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                    }
                    StringEditorSingleLine {
                        stringDecorator: newClient.ui_name
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                    }
                }
            }
            AddressEditor {
                address: newClient.ui_supplyAddress
                headerText: "Supply Address"
            }
            AddressEditor {
                address: newClient.ui_billingAddress
                headerText: "Billing Address"
            }

            ContactsEditor {
                width: scrollView.width
                client: newClient
                headerText: "Contact Details"
            }
        }
    }
    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_createClientViewContextCommands
    }
}

