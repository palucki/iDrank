import QtQuick 2.12
import assets 1.0

Item {
    property bool isCollapsed: true

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }

    width: isCollapsed ? Style.widthNavigationBarCollapsed :
                         Style.widthNavigationBarExpanded

    Rectangle {
        anchors.fill: parent
        color: Style.colorNavigationBarBackground

        Column {
            width: parent.width
            NavigationButton {
                iconCharacter: "\uf0c9"
                description: ""
                hoverColor: "#993333"
                onNavigationButtonClicked: isCollapsed  = !isCollapsed
            }
            NavigationButton {
                iconCharacter: "\uf015"
                description: "Dashboard"
                hoverColor: "#dc8a00"
                onNavigationButtonClicked: masterController.ui_navigationController.goDashboardView();
            }
            NavigationButton {
                iconCharacter: "\uf234"
                description: "New Client"
                hoverColor: "#dccd00"
                onNavigationButtonClicked: masterController.ui_navigationController.goCreateClientView();
            }
            NavigationButton {
                iconCharacter: "\uf002"
                description: "Find Client"
                hoverColor: "#8aef63"
                onNavigationButtonClicked: masterController.ui_navigationController.goFindClientView();
            }
        }
    }
}
