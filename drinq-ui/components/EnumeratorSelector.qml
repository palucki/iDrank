import QtQuick 2.12
import QtQuick.Controls 2.12

import DrinQ 1.0
import assets 1.0


Item {
    property DropDown dropDown
    property EnumeratorDecorator enumeratorDecorator

    property bool withBackground: false

    id: enumeratorSelectorRoot
    Row {
        anchors.fill: parent
//        Rectangle {
//            width: Style.widthDataControls
//            height: Style.heightDataControls
//            Text {
//                id: textLabel
//                anchors {
//                    fill: parent
//                    margins: Style.heightDataControls / 4
//                }
//                text: enumeratorDecorator.ui_label
//                color: Style.colorDataControlsFont
//                font.pixelSize: Style.pixelSizeDataControls
//                verticalAlignment: Qt.AlignVCenter
//            }
//        }

        Rectangle {
            id: buttonAnswer
            width: parent.width
            height: parent.height
            radius: Style.sizeDataControlsRadius
            enabled: dropDown ? dropDown.ui_values.length > 0 : false
            color: Style.colorDataSelectorBackground
            Text {
                id: textAnswer
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text:
                    dropDown.findDescriptionForDropdownValue(enumeratorDecorator.ui_value)
                color: Style.colorDataSelectorFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked:
                    contentFrame.push("qrc:/components/EnumeratorSelectorView.qml",
                                      {dropDown: enumeratorSelectorRoot.dropDown,
                                       enumeratorDecorator: enumeratorSelectorRoot.enumeratorDecorator})
            }
        }
    }
}
