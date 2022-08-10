import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Page {
    function goBack(event) {
        console.log("Go back function in history master view ")
        console.log("History stackView dept " + historyStackView.depth)
        //when party summary on
        if(historyStackView.depth >= 2) {
            console.log("Executing pop")
            historyStackView.pop()
        }
        else {
            masterTabBar.currentIndex = 0
        }
        event.accepted = true
    }

    Keys.onPressed: {
//        dev version
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace)
            goBack(event)
    }

    header: Label  {
            background: Rectangle {
                    color: "plum"
            }
            id: historyCenterLabel
            text: qsTr("Parties history")
            //                maximumLength: 30
            color: "black"
            font.pointSize: 14
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
    }

    StackView {
        id: historyStackView

        anchors.fill: parent
        clip: true

        initialItem: "qrc:/PartiesView.qml"
    }
}
