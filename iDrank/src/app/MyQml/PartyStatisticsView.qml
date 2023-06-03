import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.12
// import QtGraphicalEffects 1.12
import Qt5Compat.GraphicalEffects

Page {
    property string unit : "ml"
    property int partyId: partyController.ui_current_party_id
    property var drinks : drinkProvider.getUIDrinksList(partyId)
//    property date partyStarted: partyController.ui_current_party_started
    property date partyEnded

    Component.onCompleted: {
        console.log("Party statistics onCompleted series 0 " + chartView.series(0))
        plotter.setSeries(chartView.series(0), chartView.series(2), chartView.series(4), chartView.series(6))
        plotter.setAxes(axisX, axisY1)
        drinks = drinkProvider.getUIDrinksList(partyId)
        plotter.update(partyId)
    }

    Connections {
        target: partyController
        function onUi_drinksChanged()
        {
            console.log("Drinks changed in party statistics view. party Id " + partyId)
            plotter.setSeries(chartView.series(0), chartView.series(2), chartView.series(4), chartView.series(6))
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
            color: "transparent"

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

                    ScatterSeries {
                        name: qsTr("Party start / end")
                        axisX: axisX
                        axisY: axisY1
                        id: partyStart
                        color: "green"
                        pointsVisible: true
                        markerSize: 20
                    }

                    //CONSUMPTION 1
                    AreaSeries {
                        name: qsTr("Consumption (") + unit + ")"
                        axisX: axisX
                        axisY: axisY1
                        upperSeries: consumption1
                        color: "#f5a742"
                    }

                    LineSeries {
                        axisX: axisX
                        axisY: axisY1
                        id: consumption1
                        color: "#f57542"
                        width: 2
                    }
                    //CONSUMPTION 2
                    AreaSeries {
                        name: qsTr("Consumption (") + unit + ")"
                        axisX: axisX
                        axisY: axisY1
                        upperSeries: consumption2
                        color: "#4299f5"
                    }

                    LineSeries {
                        axisX: axisX
                        axisY: axisY1
                        id: consumption2
                        color: "#057bf7"
                        width: 2
                    }
                    //CONSUMPTION 3
                    AreaSeries {
                        name: qsTr("Consumption (") + unit + ")"
                        axisX: axisX
                        axisY: axisY1
                        upperSeries: consumption3
                        color: "#dce673"
                    }

                    LineSeries {
                        axisX: axisX
                        axisY: axisY1
                        id: consumption3
                        color: "#95a300"
                        width: 2
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
