import QtQuick 2.12
import DrinQ 1.0
import assets 1.0

Item {

    property Drink drink
    implicitWidth: flow.implicitWidth
    implicitHeight: flow.implicitHeight + borderBottom.implicitHeight +
                    Style.sizeItemMargin
    height: width > selectorType.width + textAddress.width +
            Style.sizeScreenMargin
            ? selectorType.height + borderBottom.height +
              Style.sizeItemMargin
            : selectorType.height + textAddress.height +
              Style.sizeScreenMargin + borderBottom.height + Style.sizeItemMargin
    Flow {
        id: flow
        width: parent.width
        spacing: Style.sizeScreenMargin
        EnumeratorSelector {
            id: selectorType
            width: Style.widthDataControls
            dropDown: drink.ui_beverageDropDown
            enumeratorDecorator: drink.ui_beverage
        }
//        StringEditorSingleLine {
//            id: textAddress
//            width: Style.widthDataControls
//            stringDecorator: drink.ui_amount_ml
//        }
        Text {
            id: textAddress
            width: Style.widthDataControls
            text: Style.amountWithUnit(drink.ui_amount_ml.ui_value)
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
