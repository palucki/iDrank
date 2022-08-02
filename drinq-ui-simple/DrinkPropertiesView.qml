import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent
        color: "lightpink"

        Column {
            anchors.centerIn: parent
            spacing: 30

            TextField {
                id: newFolderInput
                width: parent.width * 0.75
                placeholderText: "DUPA"
            }
        }
    }
}
