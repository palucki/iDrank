import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import DrinQ 1.0
import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    property DrinkType drinkType;

    Rectangle {
        anchors.fill: parent
        color: "lightpink"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 30

            Label {
                text: "Nazwa"
                width: parent.width * 0.75
            }

            TextInput {
                width: parent.width * 0.75
                text: drinkType ? drinkType.ui_name : "Name"
            }

            Label {
                text: "Domyślna ilość"
                width: parent.width * 0.75
            }

            SpinBox {
                width: parent.width * 0.75
                stepSize: 10
                from: 0
                to: 1000
                editable: true
                value: drinkType ? drinkType.ui_default_amount_ml : 50
            }

            Label {
                text: "Typ"
                width: parent.width * 0.75
            }

            RowLayout {
                RadioButton {
                    checked: drinkType ? drinkType.ui_consumption_type === DrinkType.Shot : true
                    text: qsTr("Shot")
                }
                RadioButton {
                    checked: drinkType ? drinkType.ui_consumption_type === DrinkType.Long : false
                    text: qsTr("Drink")
                }
            }
        }
    }
}
