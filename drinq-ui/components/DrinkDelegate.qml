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

    Row {
        id: flow
        width: parent.width
        spacing: Style.sizeScreenMargin
        EnumeratorSelector {
            id: selectorType
            width: Style.widthDataControls / 2
            dropDown: drink.ui_beverageDropDown
            enumeratorDecorator: drink.ui_beverage
        }

        Row {
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            spacing: Style.unitSpacing

            Text {
                id: unitText
                anchors {
                    verticalCenter: parent.verticalCenter
                }
                text: Style.amountWithUnit(drink.ui_amount_ml.ui_value)
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colorDataSelectorFont
                verticalAlignment: Qt.AlignVCenter
            }
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
