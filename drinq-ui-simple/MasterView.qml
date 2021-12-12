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


    StackView {
        id: contentFrame
        anchors.fill: parent
        clip: true
        initialItem: "qrc:DashboardView.qml"
    }

    //    Material.theme: Material.Dark
    //    Material.accent: Material.Purple

    header: ToolBar {
        id: toolbar
        property alias labelText : centerLabel.text

        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                //               onClicked: stack.pop()
            }
            Label {
                id: centerLabel
                text: "Title"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("⋮")
                //               onClicked: menu.open()
            }
        }
    }
}
