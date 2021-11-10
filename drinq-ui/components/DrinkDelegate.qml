import QtQuick 2.12
import DrinQ 1.0
import assets 1.0

Item {

    property Drink drink
    implicitWidth: flow.implicitWidth
    implicitHeight: flow.implicitHeight + borderBottom.implicitHeight +
                    Style.sizeItemMargin
    height:  selectorType.height + borderBottom.height +
              Style.sizeItemMargin

    Rectangle {
        radius: Style.sizeDataControlsRadius
        color: Style.colorDataSelectorBackground
        anchors.fill: parent
//        anchors.margins: Style.sizeItemMargin
        height: Style.heightDataControls

    }

    Row {
        id: flow
        width: parent.width
        spacing: Style.sizeItemMargin

        Text {
            id: timestampText
            width: 100 // add in style
            height: Style.heightDataControls
            anchors {
                verticalCenter: parent.verticalCenter
//                margins: 200//Style.heightDataControls / 4
            }
            text: drink.ui_consumed.ui_prettyTimeString
            horizontalAlignment: Text.AlignHCenter //TODO replace with margin left?
            font.pixelSize: Style.pixelSizeDataControls
            color: Style.colorDataSelectorFont
            verticalAlignment: Qt.AlignVCenter
        }

        Text {
            id: unitText
            width: 50 // add in style
            height: Style.heightDataControls
            anchors {
                verticalCenter: parent.verticalCenter
//                margins: Style.heightDataControls / 4
            }
            text: Style.amountWithUnit(drink.ui_amount_ml.ui_value)
            font.pixelSize: Style.pixelSizeDataControls
            color: Style.colorDataSelectorFont
            verticalAlignment: Qt.AlignVCenter
        }

        EnumeratorSelector {
            id: selectorType
            width: Style.widthDataControls / 2
            height: Style.heightDataControls
            dropDown: drink.ui_beverageDropDown
            enumeratorDecorator: drink.ui_beverage
        }


        Connections {
            target: drink.ui_beverage
            onValueChanged: {
                drink.ui_amount_ml.ui_value = drink.ui_defaultAmount(drink.ui_beverage.ui_value)
            }
        }

    }


    Rectangle {
        id: borderBottom
        anchors {
            top: flow.bottom
            left: parent.left
            right: parent.right
            topMargin: Style.sizeItemMargin
        }
        height: 1
        color: Style.colorItemBorder
    }
}
