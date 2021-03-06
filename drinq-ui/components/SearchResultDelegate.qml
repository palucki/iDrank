import QtQuick 2.12

import assets 1.0
import DrinQ 1.0

Item {
    property Client client
    implicitWidth: parent.width
    implicitHeight: Math.max(clientColumn.implicitHeight,
                             textAddress.implicitHeight) + (Style.heightDataControls / 2)
    Rectangle {
        id: background
        width: parent.width
        height: parent.height
        color: Style.colorPanelBackground
        Column {
            id: clientColumn
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
                text: client.ui_reference.ui_label + ": " +
                      client.ui_reference.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorPanelFont
            }
            Text {
                id: textName
                anchors.left: parent.left
                text: client.ui_name.ui_label + ": " +
                      client.ui_name.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorPanelFont
            }
        }
        Text {
            id: textAddress
            anchors {
                top: parent.top
                right: parent.right
                margins: Style.heightDataControls / 4
            }
            text: client.ui_supplyAddress.ui_fullAddress
            font.pixelSize: Style.pixelSizeDataControls
            color: Style.colorPanelFont
            horizontalAlignment: Text.AlignRight
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
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: masterController.selectClient(client)
        }
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
}
