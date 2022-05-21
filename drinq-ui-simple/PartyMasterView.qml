import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

import "qrc:/"

Page {

    //    header: ToolBar {
    //        id: toolbar
    //        property alias labelText : centerLabel.text

    //        RowLayout {
    //            anchors.fill: parent
    //            ToolButton {
    //                id: leftButton
    //                text: contentFrame.depth > 1 ? "<" : ""
    //                enabled: contentFrame.depth > 1
    //                onClicked: navigationController.goBack()
    //            }
    //            Label  {
    //                id: centerLabel
    //                text: "Title"
    //                //                maximumLength: 30
    //                color: "white"
    //                font.pointSize: 14
    //                elide: Label.ElideRight
    //                horizontalAlignment: Qt.AlignHCenter
    //                verticalAlignment: Qt.AlignVCenter
    //                Layout.fillWidth: true
    //            }
    //            ToolButton {
    //                id: rightButton
    //                text:  contentFrame.depth > 1 ? "" : qsTr("☰")
    //                enabled: contentFrame.depth == 1
    //                onClicked: {
    //                    contentFrame.pagesTitles.push(contentFrame.depth + " Parties")
    //                    contentFrame.push("qrc:PartiesView.qml")
    //                }
    //            }
    //        }
    //    }


    header: ColumnLayout {
        spacing: 0
        Label  {
            background: Rectangle {
                    color: "plum"
            }
            id: centerLabel
            text: "Title"
            //                maximumLength: 30
            color: "black"
            font.pointSize: 14
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }


        TabBar {
            background: Rectangle {
                    color: "plum"
            }


            Layout.fillWidth: true
//            anchors.left: parent.left
//            anchors.right: parent.right
            id: dashboardTabBar
            //        currentIndex: dashboardSwipeView.currentIndex

            TabButton {
                text: "Przeglad"
                //            icon.source: "qrc:/history.svg"
                //            display: AbstractButton.TextUnderIcon
            }
            TabButton {
                text: "Przebieg imprezy"
                //            icon.source: "qrc:/history.svg"
                //            display: AbstractButton.TextUnderIcon
            }
        }

    }




    SwipeView {
        id: dashboardSwipeView
        interactive: false
        anchors.fill: parent
        currentIndex: dashboardTabBar.currentIndex

        onCurrentIndexChanged: {
            if(currentIndex == 1)
            {
//                partyController.setPartyId()
            }
        }

        PartyDashboardView {

        }

        PartyStatisticsView {

        }
    }
}
