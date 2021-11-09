import QtQuick 2.12
import DrinQ 1.0
import assets 1.0

Panel {
    property Party party
    id: drinksEditorRoot
    contentComponent:
        Column {
        id: column
        spacing: Style.sizeControlSpacing
        Repeater {
            id: drinksView
            model: party.ui_drinks
            delegate:
                DrinkDelegate {
                width: drinksEditorRoot.width
                drink: modelData
            }
        }
        FormButton {
            iconCharacter: "\uf067"
            description: "Add drink"
            onFormButtonClicked: {
//                party.addDrink();
                contentFrame.push("qrc:/components/EnumeratorSelectorView.qml"/*,
                                  {dropDown: enumeratorSelectorRoot.dropDown,
                                   enumeratorDecorator: enumeratorSelectorRoot.enumeratorDecorator}*/)
            }
        }
    }
}
