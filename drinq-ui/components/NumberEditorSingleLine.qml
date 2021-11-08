import QtQuick 2.12
import QtQuick.Controls 2.12

import DrinQ 1.0
import assets 1.0

Item {
    property IntDecorator intDecorator
    height: width > textLabel.width + textValue.width ?
                Style.heightDataControls : Style.heightDataControls * 2
    Flow {
        anchors.fill: parent
        Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colorPanelBackground
            Text {
                id: textLabel
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: intDecorator ? intDecorator.ui_label : "ERROR"
                color: Style.colorDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }
        Row {
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            spacing: Style.unitSpacing
//            color: Style.colorDataControlsBackground
//            border {
//                width: 1
//                color: Style.colorDataControlsFont
//            }

            SpinBox {
                id: textValue
                from: 0
                to: 1000
                stepSize: 10
//                anchors {
//                    fill: parent
//                    margins: Style.heightDataControls / 4
//                }
                value: intDecorator ? intDecorator.ui_value : 0
                editable: true
//                color: Style.colorDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
//                verticalAlignment: Qt.AlignVCenter
//                suffix: Style.settings.amountUnit


                up.indicator: Rectangle {
                       x: parent.width - width
                       height: parent.height
                       implicitWidth: 40
                       implicitHeight: 40
                       color: textValue.up.pressed ? "#e4e4e4" : "#f6f6f6"
                       border.color: enabled ? "#21be2b" : "#bdbebf"

                       Text {
                           text: "+"
                           font.pixelSize: Style.pixelSizeDataControls
                           color: "#21be2b"
                           anchors.fill: parent
                           fontSizeMode: Text.Fit
                           horizontalAlignment: Text.AlignHCenter
                           verticalAlignment: Text.AlignVCenter
                       }
                   }

                   down.indicator: Rectangle {
//                       radius: 10
                       x: 0
                       height: parent.height
                       implicitWidth: 40
                       implicitHeight: 40
                       color: textValue.down.pressed ? "#e4e4e4" : "#f6f6f6"
                       border.color: enabled ? "#21be2b" : "#bdbebf"

                       Text {
                           text: "-"
                           font.pixelSize: Style.pixelSizeDataControls
                           color: "#21be2b"
                           anchors.fill: parent
                           fontSizeMode: Text.Fit
                           horizontalAlignment: Text.AlignHCenter
                           verticalAlignment: Text.AlignVCenter
                       }
                   }

            }

            Text {
                id: unitText
                anchors {
                    verticalCenter: parent.verticalCenter
                }
                text: Style.settings.amountUnit
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }

//            TextInput {
//                id: textValue
//                anchors {
//                    fill: parent
//                    margins: Style.heightDataControls / 4
//                }
//                text: intDecorator ? intDecorator.ui_value : "ERROR"
//                color: Style.colorDataControlsFont
//                font.pixelSize: Style.pixelSizeDataControls
//                verticalAlignment: Qt.AlignVCenter
//            }
        }
        Binding {
            target: intDecorator
            property: "ui_value"
            value: textValue.value
        }
    }
}
