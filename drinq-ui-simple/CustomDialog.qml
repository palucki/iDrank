import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Dialog {
    property alias dialogTitle: dialog.title
    property alias dialogPlaceholderText: newFolderInput.placeholderText
    property alias dialogText: newFolderInput.text
    property bool allowEmpty : false


    function openDialog() {
        newFolderInput.text = ""
        dialog.open()
    }

    id: dialog
    anchors.centerIn: parent
    height: 250
    width: 300
    standardButtons: Dialog.Ok | Dialog.Cancel
    focus: true
    Column {
        anchors.fill: parent
        TextField {
            id: newFolderInput
            width: parent.width * 0.75
            focus: true
            //                        onFocusChanged: console.log("Focus changed " + focus)
        }
    }
}
