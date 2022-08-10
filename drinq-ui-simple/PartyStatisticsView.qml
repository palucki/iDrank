import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.12

Page {
    property string unit : "ml"
    property int partyId: partyController.ui_current_party_id
    property var drinks : drinkProvider.getUIDrinksList(partyId)
//    property date partyStarted: partyController.ui_current_party_started
    property date partyEnded

    Component.onCompleted: {
        console.log("Party statistics onCompleted series 0 " + chartView.series(0))
        plotter.setSeries(chartView.series(0), chartView.series(2))
        plotter.setAxes(axisX, axisY1)
        drinks = drinkProvider.getUIDrinksList(partyId)
        plotter.update(partyId)
    }

    Connections {
        target: partyController
        function onUi_drinksChanged()
        {
            console.log("Drinks changed in party statistics view. party Id " + partyId)
            plotter.setSeries(chartView.series(0), chartView.series(2))
            plotter.setAxes(axisX, axisY1)
            drinks = drinkProvider.getUIDrinksList(partyId)
            plotter.update(partyId)
        }
    }

    ConfirmationDialog {
        id: deleteDrinkConfirmationDialog
        standardButtons: Dialog.Ok | Dialog.Cancel
    }

    ScrollView {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "skyblue"

            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                width: parent.width

                ChartView {
                    height: 400
                    width: parent.width
                    id: chartView
                    antialiasing: true

                    ValueAxis {
                        id: axisY1
                    }

                    DateTimeAxis{
                        id: axisX
                        labelsAngle: 270
                        format: "ddd hh:mm"
                    }

                    AreaSeries {
                        name: qsTr("Consumption (") + unit + ")"
                        axisX: axisX
                        axisY: axisY1
                        upperSeries: consumption
                    }

                    LineSeries {

                        axisX: axisX
                        axisY: axisY1
                        id: consumption
                        color: "red"
                        width: 2

                    }

                    ScatterSeries {
                        name: qsTr("Party start / end")
                        axisX: axisX
                        axisY: axisY1
                        id: partyStart
                        color: "green"
                        pointsVisible: true
                        markerSize: 20
                    }

                }

                ListView {
                    id: drinksList
                    height: 200
                    width: parent.width
                    clip: true
                    model: drinks
                    delegate: drinkTypeDelegate
                    spacing: 5
                }

                Component {
                    id: drinkTypeDelegate

                    Rectangle {
                        width: drinksList.width
                        height: 40

                        color: ListView.isCurrentItem?"#157efb" : "transparent"
                        border.color: Qt.lighter(color, 1.1)

                        Text {
                            anchors.left: parent.left
                            font.pixelSize: 10
                            text: drinkController.type(modelData.ui_drink_type_id) + " " + modelData.ui_amount_ml + " " + unit + " (" + modelData.ui_timestamp + ")"
                        }

                        Button {
                            focusPolicy: Qt.NoFocus
                            anchors.right: parent.right
                            text: "X"
                            onClicked: {
                                deleteDrinkConfirmationDialog.openDialog(qsTr("Delete the drink?"))
                                deleteDrinkConfirmationDialog.accepted.connect(function(){
                                    console.log("DELETE drink")
                                    partyController.deleteDrink(modelData.ui_id)
                                })
                            }
                        }
                    }
                }
            }
        }
    }
}
