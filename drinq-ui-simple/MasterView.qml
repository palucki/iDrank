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

    Popup {
        id: masterPopup
        anchors.centerIn: parent
        height:parent.height
        width: parent.width
        contentItem: Text {
            text: "Content"
            MouseArea {
                anchors.fill: parent
                onClicked: masterPopup.close()
            }
        }
        onOpened: {
            console.log("Selecting another toast")
        }
    }

    StackView {
        property var pagesTitles : ["Test"]

        id: contentFrame
        anchors.fill: parent
        clip: true
        initialItem: "qrc:DashboardView.qml"
        onCurrentItemChanged: {
            console.log("contents changed")
//            toolbar.labelText = contentFrame.pagesTitles.at(-1) //means: last item
            toolbar.labelText = contentFrame.pagesTitles[contentFrame.pagesTitles.length - 1] //means: last item
        }

        //        onDepthChanged: {
        //            if(depth > 1) {
        //                leftButton.enabled = true
        //                leftButton.text = "<"
        //            } else {
        //                leftButton.enabled = true
        //                leftButton.text = "<"
        //            }
        //        }
    }

    //    Material.theme: Material.Dark
    //    Material.accent: Material.Purple

    header: ToolBar {
        id: toolbar
        property alias labelText : centerLabel.text

        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: leftButton
                text: contentFrame.depth > 1 ? "<" : ""
                enabled: contentFrame.depth > 1
                onClicked: {
                    contentFrame.pagesTitles.pop()
                    toolbar.labelText = contentFrame.pagesTitles[contentFrame.pagesTitles.length - 1]
                    contentFrame.pop()
                }
                //               onClicked: stack.pop()
            }
            Label  {
                id: centerLabel
                text: "Title"
//                maximumLength: 30
                color: "white"
                font.pointSize: 14
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                id: rightButton
                text:  contentFrame.depth > 1 ? "" : qsTr("☰")
                enabled: contentFrame.depth == 1
                onClicked: {
                    contentFrame.pagesTitles.push(contentFrame.depth + " Parties")
                    contentFrame.push("qrc:PartiesView.qml")                    
                }
            }
        }
    }
}
