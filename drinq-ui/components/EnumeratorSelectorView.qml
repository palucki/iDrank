import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import DrinQ 1.0
import assets 1.0

Item {
    id: stringSelectorView
    property DropDown dropDown
    property EnumeratorDecorator enumeratorDecorator
    property int selectedValue

    ScrollView {
        id: scrollView
        visible: true
        anchors.fill: parent
        anchors {
            top: parent.bottom
            left: parent.left
            right: parent.right
            bottom: parent.top
            margins: Style.sizeScreenMargin
        }
        Column {
//            flow: Grid.TopToBottom
            spacing: Style.sizeControlSpacing
            height: scrollView.height


            ////////////////////


            TextInput {
                opacity: 1
                id: li_userinput_edit
                font.pixelSize: Style.pixelSizeDataControls
                inputMask: "00:00"
                cursorVisible: true
                inputMethodHints: Qt.ImhTime
                text: "00:00"
//              onAccepted: currentintervall = li_userinput_edit.text
                validator: RegExpValidator { regExp: /^(?:(?:([01]?\d|2[0-3]):)?([0-5]?\d):)?$/ }
            }


//            TextField{
//                id:textEditTD
//                text : "00:00:00"
//                inputMask: "99:99:99"
//                inputMethodHints: Qt.ImhDigitsOnly
//                validator: RegExpValidator { regExp: /^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):[0-5][0-9]$ / }

//                width:100
//                height:50
//                background:Rectangle{
//                    color:"transparent"
//                    border.color: "red"
//                    border.width:2
//                    radius:(width * 0.05)
//                }
//            }

            //


            Rectangle {
                id: background
                width: Style.widthDataControls
                height: Style.heightDataControls
                radius: Style.sizeDataControlsRadius
                color: Style.colorDataSelectorBackground
//                spacing: Style.unitSpacing

//                Rectangle {
//                    color: black
//                    width: Style.widthDataControls
//                    height: Style.heightDataControls
//                }


                SpinBox {
                    id: textValue
                    from: 0             //move to style
                    to: 1000            //move to style
                    stepSize: 10        // move to style
                    value: 0
                    //                    value: intDecorator ? intDecorator.ui_value : 0
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
                        left: textValue.right
                    }
    //                text: intDecorator ? Style.amountWithUnit(intDecorator.ui_value) :  ""
                    text: Style.settings.amountUnit
                    font.pixelSize: Style.pixelSizeDataControls
                    color: Style.colorDataSelectorFont
                    verticalAlignment: Qt.AlignVCenter
                }
            }
            /////////////////////

//            ComboBox {
//                model: dropDown.ui_values
//            }



            /////////////////////



            Repeater {
                id: repeaterAnswers
                model: dropDown.ui_values
//                textRole: "ui_description"

//                onCurrentIndexChanged: {
//                    selectedValue = currentIndex
//                }

//                valueRole: "value"
                delegate:
                    Rectangle {
                    property bool isSelected: modelData.ui_key.ui_value
                                              === enumeratorDecorator.ui_value
                    width: Style.widthDataControls
                    height: Style.heightDataControls

//                    radius: Style.sizeDataControlsRadius
                    color: isSelected ?
                               Style.colorDataControlsBackgroundSelected :
                               Style.colorDataSelectorBackground
                    Text {
                        anchors {
                            fill: parent
                            margins: Style.heightDataControls / 4
                        }
                        text: modelData.ui_description
                        color: Style.colorDataSelectorFont
                        font.pixelSize: Style.pixelSizeDataControls
                        verticalAlignment: Qt.AlignVCenter
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            selectedValue = modelData.ui_key;
                            contentFrame.pop();
                        }
                    }
                }
            }

        }
    }

    Binding {
        target: enumeratorDecorator
        property: "ui_value"
        value: selectedValue
    }
}
