import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Dialog {
    property alias dialogTitle: dialog.title
    property alias dialogPlaceholderText: newFolderInput.placeholderText
    property alias dialogText: newFolderInput.text

    function openDialog() {
        newFolderInput.text = ""
        dialog.open()
    }

    id: dialog
    modal: true
    anchors.centerIn: parent
    height: 250
    width: 300

    //Note: it is not correct to use standardButtons: Dialog.Ok or others here
    //it will lead to memory leak

    Column {
        anchors.fill: parent
        TextField {
            id: newFolderInput
            width: parent.width * 0.75
            focus: true
        }

        Button {
            text: "Ok"
            onClicked: {
                dialog.accept()
            }
        }
    }
}
