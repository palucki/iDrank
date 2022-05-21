import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

Item {

    focus:true

    function goBack() {
        console.log("Go back function in history master view ")

        if(historyStackView.depth == 2) //when party summary on
        {
            console.log("Executing pop")
            historyStackView.pop()
        }
        //            else
        //                Qt.quit()
    }

    Keys.onPressed: {
//        dev version
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Backspace)
            goBack()

//            console.log("Pressed key " + event.key)
    }

//    Connections {
//        target: navigationController
//        function onGoBack() {
//            console.log("Go back in history master view")
//        }
//    }

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
