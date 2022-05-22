import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.12

Item {
    property string unit : "ml"

    function updateChart() {
        partyController.update(chartView.series(0), chartView.series(2))

        axisX.min = partyController.plot_min()
        axisX.max = partyController.plot_max()
        console.log("setting max to " + partyController.ui_plot_max_value + 20)
        axisY1.max = partyController.ui_plot_max_value + 20
    }

    Component.onCompleted: updateChart()

    Connections {
        target: partyController
        function onUi_drinksChanged(){  updateChart() }
    }

    ScrollView {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "skyblue"

            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30

                width: parent.width

                ChartView {
                    height: 400
                    width: parent.width
                    id: chartView
                    antialiasing: true

                    ValueAxis {
                        id: axisY1
                        min: 0
//                        max: 1000 /*partyController.ui_plot_max_value() + 10*/
                    }

                    DateTimeAxis{
                        id: axisX
                        //                    min: partyController.plot_min()
                        //                    max: partyController.plot_max()
                        labelsAngle: 270
                        format: "ddd hh:mm"
                    }

                    AreaSeries {
                        name: "Consumption (" + unit + ")"
                        axisX: axisX
                        axisY: axisY1
                        upperSeries: consumption
                        //                    upperSeries: /*consumption*/ LineSeries {
                        //                        id: consumption
                        //                    }
                    }

                    LineSeries {

                        axisX: axisX
                        axisY: axisY1
                        id: consumption
                        pointsVisible: true
                        color: "red"
                        width: 2

                    }

                    ScatterSeries {
                        name: "Party start"
                        axisX: axisX
                        axisY: axisY1
                        id: partyStart
                        color: "green"
                        pointsVisible: true
                        markerSize: 20

                    }

                }

                ListView {
                    //                    anchors.fill: parent
                    id: drinksList
                    height: 200
                    width: parent.width
                    anchors.margins: 20

                    clip: true

                    model: partyController.ui_drinks

                    delegate: drinkTypeDelegate
                    spacing: 5

//                    focus: true
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

                        //to hightliht
                        //                    MouseArea {
                        //                        anchors.fill: parent
                        //                        onClicked: drinksList.currentIndex = index
                        //                    }

                        Button {
                            anchors.right: parent.right
                            text: "X"
                            onClicked: {
                                console.log("DELETE drink")
                                partyController.deleteDrink(modelData.ui_id)
                            }
                        }
                    }
                }
            }


            //        Column {
            //            anchors.centerIn: parent
            //            spacing: 30



            //            Row {
            //                anchors.horizontalCenter: parent.horizontalCenter
            //                //                width: parent.width
            //                //                height: 60
            //                spacing: 60

            //                RoundButton {
            //                    id: partyButton
            //                    anchors.verticalCenter: parent.verticalCenter
            //                    height: 100
            //                    width: 100
            //                    text: "Cancel"
            //                    font.pointSize: 10
            //                    Material.background: Material.Purple
            //                    onClicked: {
            //                        console.log("Cancel")
            //                        navigationController.goBack()
            //                    }
            //                }

            //                RoundButton {
            //                    id: typeButton
            //                    anchors.verticalCenter: parent.verticalCenter
            //                    height: 100
            //                    width: 100
            //                    text: "Chart"
            //                    font.pointSize: 10
            //                    Material.background: Material.LightGreen
            //                    onClicked: {
            //                        contentFrame.pagesTitles.push(contentFrame.depth + " Chart")
            //                        contentFrame.push("qrc:PartyStatisticsView.qml")
            //                    }
            //                }
            //            }
            //        }
        }
    }
}
