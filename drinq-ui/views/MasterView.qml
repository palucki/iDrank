import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml 2.12
import QtQuick.Controls 2.2

import assets 1.0
import components 1.0

Window {
    width: Style.widthWindow
    height: Style.heightWindow
    visible: true
    title: qsTr("Drinking counter")

    Component.onCompleted: {
        if(!splashViewTimerId.running) {
            console.log("Component load completed")
            contentFrame.replace("qrc:/views/DashboardView.qml")
        }
    }

    Timer {
        id: splashViewTimerId
        interval: Style.config.splashScreenTimeoutMs;
        running: true;
        repeat: false
        onTriggered: {
            console.log("Timer completed")
            contentFrame.replace("qrc:/views/DashboardView.qml")
        }

    }

    Connections {
        target: masterController.ui_navigationController

        onGoCreateClientView: contentFrame.replace("qrc:/views/CreateClientView.qml")
        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoEditClientView: contentFrame.replace("qrc:/views/EditClientView.qml", {selectedClient: client})
        onGoFindClientView: contentFrame.replace("qrc:/views/FindClientView.qml")
    }

    NavigationBar {
        id: navigationBar
    }

    StackView {
        id: contentFrame
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left : navigationBar.right
        }
        clip: true
        initialItem: "qrc:/views/SplashView.qml"
        // Qt.resolvedUrl("qrc:/views/SplashView.qml")
    }
}
