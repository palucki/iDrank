import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Page {
    property DrinkType drinkType;
    property int drink_index;

    function saveDrinkType() {
        if(drinkType) {
            drink_type_controller.update(drink_index, drinkType.ui_id, drinkTypeName.text, drinkTypeDefaultAmount.value, 12)
        }
        else {
            drink_type_controller.add(drinkTypeName.text, drinkTypeDefaultAmount.value, 11)
        }
    }

    header: Rectangle {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTranslate("DrinkProperties", "‹")
                onClicked: partyDashboardStackView.pop()
            }
            Label {
                text: qsTranslate("DrinkProperties", "Edit drink type")
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTranslate("DrinkProperties", "Save")
                onClicked: {
                    saveDrinkType()
                    partyDashboardStackView.pop()
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 30

            Label {
                text: qsTranslate("DrinkProperties", "Name")
                width: parent.width * 0.75
            }

            TextInput {
                id: drinkTypeName
                width: parent.width * 0.75
                text: drinkType ? drinkType.ui_name : qsTranslate("DrinkProperties", "Name")
            }

            Label {
                text: qsTranslate("DrinkProperties", "Default amount")
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
        }
    }
}
