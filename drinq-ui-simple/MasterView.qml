import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import QtQuick.Layouts 1.12

import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: root

    width: 480
    height: 720
    visible: true
    title: qsTr("iDrunk")

    Item {
        id: navigationController
        signal goBack
        onGoBack: {
            console.log("Go back")
            contentFrame.pagesTitles.pop()
            toolbar.labelText = contentFrame.pagesTitles[contentFrame.pagesTitles.length - 1]
            contentFrame.pop()
        }
    }

    //    StackView {
    //        property var pagesTitles : masterController.ui_party_started ? [masterController.ui_party_title] : [""]

    //        id: contentFrame
    //        anchors.fill: parent
    //        clip: true
    //        initialItem: masterController.ui_party_started ? "qrc:PartyDashboardView.qml" : "qrc:DashboardView.qml"
    //        onCurrentItemChanged: {
    //            console.log("contents changed")
    ////            toolbar.labelText = contentFrame.pagesTitles.at(-1) //means: last item
    //            toolbar.labelText = contentFrame.pagesTitles[contentFrame.pagesTitles.length - 1] //means: last item
    //        }

    //        //        onDepthChanged: {
    //        //            if(depth > 1) {
    //        //                leftButton.enabled = true
    //        //                leftButton.text = "<"
    //        //            } else {
    //        //                leftButton.enabled = true
    //        //                leftButton.text = "<"
    //        //            }
    //        //        }
    //    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        interactive: false

        //DashboardView (StackView / StackLayout):
            //StartPartyView (party nie zaczete, "rozpocznij spozycie")
            //PartyDashboardView (party zaczete, tutaj mamy ten swipe view z przeglad / przebieg imprezy

        //HistoryView - tutaj mamy stack layout, a moze bardziej stackView, zeby robic push z argumentami i pop
            //lista imprez
            //szzegoly imprezy  wybranej

        //AboutView

        currentIndex: tabBar.currentIndex

        DashboardView {
            id: dashboardView
        }

        PartiesView {
            id: partiesView
        }

        AboutView {
            id: aboutView
        }
    }

    footer: TabBar {
        id: tabBar
//        currentIndex: swipeView.currentIndex

        TabButton {
            text: "Home"
            icon.source: "qrc:/history.svg"
            display: AbstractButton.TextUnderIcon
        }
        TabButton {
            text: "History"
            icon.source: "qrc:/history.svg"
            display: AbstractButton.TextUnderIcon
        }
        TabButton {
            text: "About"
            icon.source: "qrc:/history.svg"
            display: AbstractButton.TextUnderIcon
        }
    }

    //    Material.theme: Material.Dark
    //    Material.accent: Material.Purple
}
