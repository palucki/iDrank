import QtQuick 2.12

import assets 1.0
import DrinQ 1.0

Item {
    property Party party
    implicitWidth: parent.width
    implicitHeight: Math.max(leftColumn.implicitHeight,
                             rightColumn.implicitHeight) + (Style.heightDataControls / 2)
    Rectangle {
        id: background
        width: parent.width
        height: parent.height
        color: Style.colorPanelBackground
        Column {
            id: leftColumn
            width: parent / 2
            anchors {
                left: parent.left
                top: parent.top
                margins: Style.heightDataControls / 4
            }
            spacing: Style.heightDataControls / 2
            Text {
                id: textReference
                anchors.left: parent.left
                text: party.ui_title.ui_label + ": " +
                      party.ui_title.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorPanelFont
            }
            Text {
                id: textName
                anchors.left: parent.left
                text: party.ui_notes.ui_label + ": " +
                      party.ui_notes.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorPanelFont
            }
        }

        Column {
            id: rightColumn
            width: parent / 2
            anchors {
                right: parent.right
                top: parent.top
                margins: Style.heightDataControls / 4
            }
            spacing: Style.heightDataControls / 2

            Text {
                id: textAddress
                anchors {
                    right: parent.right
                    margins: Style.heightDataControls / 4
                }
                text: party.ui_started.ui_prettyDateString
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorPanelFont
                horizontalAlignment: Text.AlignRight
            }

            Text {
                id: textAddress2
                anchors {
                    right: parent.right
                    margins: Style.heightDataControls / 4
                }
                text: amountWithUnit(party.ui_amount_consumed)
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorPanelFont
                horizontalAlignment: Text.AlignRight
            }

        }

        Rectangle {
            id: borderBottom
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            height: 1
            color: Style.colorPanelFont
        }
//        MouseArea {
//            anchors.fill: parent
//            cursorShape: Qt.PointingHandCursor
//            hoverEnabled: true
//            onEntered: background.state = "hover"
//            onExited: background.state = ""
//            onClicked: masterController.selectClient(client)
//        }
        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: Style.colorPanelBackgroundHover
                }
            }
        ]
    }

    function amountWithUnit(amount) {
        //amount is always in ml
        const unit = Style.settings.amountUnit;
        switch (unit) {
        case 'l':
            amount = amount / 1000.0
            break;
        case 'ml':
            break;
        default:
            console.log("Incorrect unit in settings")
        }

        return amount + " " + unit
    }
}
