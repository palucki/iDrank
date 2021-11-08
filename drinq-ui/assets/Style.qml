pragma Singleton
import QtQuick 2.12

Item {
    // Configuration Part
    readonly property Item settings : Item {
        readonly property string amountUnit: "ml"
    }

    function amountWithUnit(amount) {
        //amount is always in ml
        const unit = settings.amountUnit;
        switch (unit) {
        case 'l':
            amount = amount / 1000.0
            break;
        case 'ml':
            break;
        default:
            console.log("Incorrect unit in settings")
        }

        return amount + " " + unit
    }


    // Configuration Part
    readonly property Item config : Item {
        readonly property int splashScreenTimeoutMs: 10
    }

    //Background
    readonly property color colorBackground: "#efefef" //#f4c842

    //Scalling
    readonly property real widthWindow: 520
    readonly property real heightWindow: 960

    readonly property real widthWindowReference: 520
    readonly property real heightWindowReference: 960

    function hscale(size) {
        return Math.round(size * (widthWindow / widthWindowReference))
    }
    function vscale(size) {
        return Math.round(size * (heightWindow / heightWindowReference))
    }
    function tscale(size) {
        return Math.round((hscale(size) + vscale(size)) / 2)
    }

    readonly property color colorDashboardBackground: "#f36f24"
    readonly property color colorDashboardFont: "#ffffff"
    readonly property int pixelSizeDashboard: tscale(36)
    readonly property real sizeDashboardLogo: tscale(500)

    //Navigation Pane
    readonly property color colorNavigationBarBackground: "#000000"
    readonly property color colorNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarIcon: 42
    readonly property int pixelSizeNavigationBarText: 22

    readonly property real widthNavigationButtonIcon: 80
    readonly property real heightNavigationButtonIcon: widthNavigationButtonIcon
    readonly property real widthNavigationButtonDescription: 240
    readonly property real heightNavigationButtonDescription: heightNavigationButtonIcon
    readonly property real widthNavigationButton: widthNavigationButtonIcon + widthNavigationButtonDescription
    readonly property real heightNavigationButton: Math.max(heightNavigationButtonIcon, heightNavigationButtonDescription)

    readonly property real widthNavigationBarCollapsed: widthNavigationButtonIcon
    readonly property real widthNavigationBarExpanded: widthNavigationButton

    //Command Bar
    readonly property color colorCommandBarBackground: "#cecece"
    readonly property color colorCommandBarFont: "#131313"
    readonly property color colorCommandBarFontDisabled: "#636363"
    readonly property real heightCommandBar: heightCommandButton
    readonly property int pixelSizeCommandBarIcon: 32
    readonly property int pixelSizeCommandBarText: 12
    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton

    //CreateClientView
    readonly property real sizeScreenMargin: tscale(20)
    readonly property color colorDataControlsBackground: "#ffffff"
    readonly property color colorDataControlsFont: "#131313"
    readonly property int pixelSizeDataControls: 18
    readonly property real widthDataControls: 400
    readonly property real heightDataControls: 40


    //Panel
    readonly property real sizeControlSpacing: 10
    readonly property color colorPanelBackground: "#ffffff"
    readonly property color colorPanelBackgroundHover: "#ececec"
    readonly property color colorPanelHeaderBackground: "#131313"
    readonly property color colorPanelHeaderFont: "#ffffff"
    readonly property color colorPanelFont: "#131313"
    readonly property int pixelSizePanelHeader: 18
    readonly property real heightPanelHeader: 40
    readonly property real sizeShadowOffset: 5
    readonly property color colorShadow: "#dedede"

    //Fonts

    property alias fontAwesome: fontAwesomeLoader.name

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }

    //Contact Type Enum
    readonly property color colorDataSelectorBackground: "#131313"
    readonly property color colorDataControlsBackgroundSelected: "#f36f24"
    readonly property color colorDataSelectorFont: "#ffffff"
    readonly property int sizeDataControlsRadius: tscale(5)

    //Contact Editor
    readonly property real widthFormButton: 240
    readonly property real heightFormButton: 60
    readonly property color colorFormButtonBackground: "#f36f24"
    readonly property color colorFormButtonFont: "#ffffff"
    readonly property int pixelSizeFormButtonIcon: 32
    readonly property int pixelSizeFormButtonText: 22
    readonly property int sizeFormButtonRadius: 5

    readonly property int unitSpacing: 5

    //Other
    readonly property color colorItemBackground: "#fefefe"
    readonly property color colorItemBackgroundHover: "#efefef"
    readonly property color colorItemBorder: "#efefef"
    readonly property color colorItemDateFont: "#636363"
    readonly property color colorItemTitleFont: "#131313"
    readonly property real sizeItemMargin: 5
}
