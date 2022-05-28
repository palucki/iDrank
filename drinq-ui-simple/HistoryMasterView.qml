import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Page {

    focus: true

    function goBack(event) {
        console.log("Go back function in history master view ")

        //when party summary on
        if(historyStackView.depth >= 2) {
            console.log("Executing pop")
            historyStackView.pop()
        }
        else {
            masterTabBar.currentIndex = 0
            event.accepted = true
        }

        //            else
        //                Qt.quit()
    }

    Keys.onPressed: {
//        dev version
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace)
            goBack(event)

//            console.log("Pressed key " + event.key)
    }

//    Connections {
//        target: navigationController
//        function onGoBack() {
//            console.log("Go back in history master view")
//        }
//    }

    header: Label  {
            background: Rectangle {
                    color: "plum"
            }
            id: historyCenterLabel
            text: "Historia imprez"
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

        initialItem: "qrc:PartiesView.qml"

//        focus: true



//        Keys.onBackPressed: goBack()

//        Keys.onPressed: {
////        dev version
//            if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace)
//                goBack()

//            console.log("Pressed key " + event.key)
//        }
    }
}
