import QtQuick 2.12
import assets 1.0

Item {
    implicitWidth: parent.width
    implicitHeight: headerBackground.height +
                    contentLoader.implicitHeight + (Style.sizeControlSpacing * 2)

    property alias headerText: title.text
    property alias contentComponent: contentLoader.sourceComponent

    Rectangle {
        id: shadow
        width: parent.width
        height: parent.height
        x: Style.sizeShadowOffset
        y: Style.sizeShadowOffset
        color: Style.colorShadow
    }
    Rectangle {
        id: headerBackground
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: Style.heightPanelHeader
        color: Style.colorPanelHeaderBackground
        Text {
            id: title
            text: "Set Me!"
            anchors {
                fill: parent
                margins: Style.heightDataControls / 4
            }
            color: Style.colorPanelHeaderFont
            font.pixelSize: Style.pixelSizePanelHeader
            verticalAlignment: Qt.AlignVCenter
        }
    }
    Rectangle {
        id: contentBackground
        anchors {
            top: headerBackground.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        color: Style.colorPanelBackground
        Loader {
            id: contentLoader
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                margins: Style.sizeControlSpacing
            }
        }
    }
}
