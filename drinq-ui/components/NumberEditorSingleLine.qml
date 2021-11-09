import QtQuick 2.12
import QtQuick.Controls 2.12

import DrinQ 1.0
import assets 1.0

Item {
    property IntDecorator intDecorator
    height: Style.heightDataControls
    Flow {
        anchors.fill: parent
//        Rectangle {
//            width: Style.widthDataControls
//            height: Style.heightDataControls
//            color: Style.colorPanelBackground
//            Text {
//                id: textLabel
//                anchors {
//                    fill: parent
//                    margins: Style.heightDataControls / 4
//                }
//                text: intDecorator ? intDecorator.ui_label : "ERROR"
//                color: Style.colorDataControlsFont
//                font.pixelSize: Style.pixelSizeDataControls
//                verticalAlignment: Qt.AlignVCenter
//            }
//        }
        Row {
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            spacing: Style.unitSpacing

            SpinBox {
                id: textValue
                from: 0             //move to style
                to: 1000            //move to style
                stepSize: 10        // move to style
                value: intDecorator ? intDecorator.ui_value : 0
                editable: true
                font.pixelSize: Style.pixelSizeDataControls

                background: Rectangle {
                    implicitWidth: 140
                    border.color: "#bdbebf"
                    color: Style.colorDataSelectorBackground
                }

                palette.text: Style.colorDataSelectorFont
            }

            Text {
                id: unitText
                anchors {
                    verticalCenter: parent.verticalCenter
                }
//                text: intDecorator ? Style.amountWithUnit(intDecorator.ui_value) :  ""
                text: Style.settings.amountUnit
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorDataSelectorFont
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Binding {
            target: intDecorator
            property: "ui_value"
            value: textValue.value
        }
    }
}
