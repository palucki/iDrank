import QtQuick 2.12

import DrinQ 1.0
import assets 1.0

Item {
    property Command command
    width: Style.widthCommandButton
    height: Style.heightCommandButton

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colorCommandBarBackground

        Text {
            id: textIcon
            anchors {
                centerIn: parent
                verticalCenterOffset: -10
            }

            font {
                family: Style.fontAwesome
                pixelSize: Style.pixelSizeCommandBarIcon
            }

            color: command.ui_canExecute ? Style.colorCommandBarFont : Style.colorCommandBarFontDisabled
            text: command.ui_iconCharacter

            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: textDescription
            anchors {
                top: textIcon.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }

            font.pixelSize: Style.pixelSizeCommandBarText
            color: command.ui_canExecute ? Style.colorCommandBarFont : Style.colorCommandBarFontDisabled

            text: command.ui_description
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: if(command.ui_canExecute) {
                           command.executed();
                       }
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: Qt.darker(Style.colorCommandBarBackground)
                }
            }
        ]
    }
}
