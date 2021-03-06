import QtQuick 2.12
import DrinQ 1.0
import assets 1.0

Panel {
    property Address address
    contentComponent:
        Column {
        id: column
        spacing: Style.sizeControlSpacing
        StringEditorSingleLine {
            stringDecorator: address.ui_building
            anchors {
                left: parent.left
                right: parent.right
            }
        }
        StringEditorSingleLine {
            stringDecorator: address.ui_street
            anchors {
                left: parent.left
                right: parent.right
            }
        }
        StringEditorSingleLine {
            stringDecorator: address.ui_city
            anchors {
                left: parent.left
                right: parent.right
            }
        }
        StringEditorSingleLine {
            stringDecorator: address.ui_postcode
            anchors {
                left: parent.left
                right: parent.right
            }
        }
    }
}
