import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Dialog {
    function openDialog(labelText) {
        dialogLabel.text = labelText
        open()
    }

    //focus to true to block navigation
    focus: true
    modal: true
    anchors.centerIn: parent
    height: 250
    width: 300
    Label {
        width: parent.width
        id: dialogLabel
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
    }

    standardButtons: Dialog.Ok | Dialog.Cancel
}
