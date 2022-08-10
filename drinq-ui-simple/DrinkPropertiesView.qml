import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import DrinQ 1.0
import QtQml 2.12
import QtQuick.Layouts 1.12

Page {
    property DrinkType drinkType;

    function saveDrinkType() {
        if(drinkType) {
            drinkType.ui_name = drinkTypeName.text
            drinkType.ui_default_amount_ml = drinkTypeDefaultAmount.value
            drinkType.ui_consumption_type = drinkTypeShot.checked ? DrinkType.Shot : DrinkType.Long
            drinkController.updateDrinkType(drinkType)
        }
        else {
            drinkController.addDrinkType(drinkTypeName.text, drinkTypeDefaultAmount.value,
                                         drinkTypeShot.checked ? DrinkType.Shot : DrinkType.Long)
        }
    }

    header: Rectangle {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                onClicked: partyDashboardStackView.pop()
            }
            Label {
                text: qsTr("Edit drink type")
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("Save")
                onClicked: {
                    saveDrinkType()
                    partyDashboardStackView.pop()
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "lightpink"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 30

            Label {
                text: qsTr("Name")
                width: parent.width * 0.75
            }

            TextInput {
                id: drinkTypeName
                width: parent.width * 0.75
                text: drinkType ? drinkType.ui_name : qsTr("Name")
            }

            Label {
                text: qsTr("Default amount")
                width: parent.width * 0.75
            }

            SpinBox {
                id: drinkTypeDefaultAmount
                width: parent.width * 0.75
                stepSize: 10
                from: 0
                to: 1000
                editable: true
                value: drinkType ? drinkType.ui_default_amount_ml : 50
            }

            Label {
                text: qsTr("Type")
                width: parent.width * 0.75
            }

            RowLayout {
                RadioButton {
                    id: drinkTypeShot
                    checked: drinkType ? drinkType.ui_consumption_type === DrinkType.Shot : true
                    text: qsTr("Shot")
                }
                RadioButton {
                    id: drinkTypeLong
                    checked: drinkType ? drinkType.ui_consumption_type === DrinkType.Long : false
                    text: qsTr("Drink")
                }
            }
        }
    }
}
