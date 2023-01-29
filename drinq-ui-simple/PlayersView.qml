import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {
    Rectangle {
        anchors.fill: parent

        ListView {
            width: parent.width
            height: parent.height

            model: ["Player 1", "Player 2", "Player 3"]
            delegate: CheckDelegate {
                text: modelData
            }
        }
    }
}
