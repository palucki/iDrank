import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.12
import Qt5Compat.GraphicalEffects

Page {
    property string unit : "ml"
    property string series_name : "line"
    property var colors : ["#ffd275", "#a57f60", "#e3a587", "#db5a42", "#e8ae68", "#f4ac32"]
    property int max_colors : colors.length
    property var users;
    property var party_id;

    function createSeries(name, color) {
        console.log("adding series " + name)
        var series = chart.createSeries(ChartView.SeriesTypeLine, name, xAxis, yAxis);
        series.pointsVisible = true;
        series.color = color //Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        var pointsCount = Math.round(Math.random() * 20);
        var x = 0.0;
        for(var j = 0; j < pointsCount; j ++) {
            x += (Math.random() * 2.0);
            var y = (Math.random() * 10.0);
            series.append(x, y);
        }

        return series
    }

    Component.onCompleted: {
        console.log("party statistics for party id " + party_id + " users " + users.length)
        party_plotter.setAxes(xAxis, yAxis)
        for(var i = 0; i < users.length; i++)
        {
            party_plotter.addSeries(createSeries(users[i].ui_name, colors[i % max_colors]))
        }
        party_plotter.plot(party_id)
    }

    Connections {
        target: party_controller
        function onUi_drinks_countChanged()
        {
            console.log("Drinks changed in party statistics view. party Id " + party_id)
            party_plotter.plot(party_id)
        }
}

    ColumnLayout {
        id: layoutRoot
        anchors.fill: parent

        RowLayout {
            Layout.maximumHeight: 40

            Repeater {
                model: users
                Rectangle {
                    id: background
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    border.width: 1
                    color: colors[index % max_colors]

                    Text {
                        text: modelData.ui_name
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { 
                            party_plotter.toggleVisibility(modelData.ui_name)
                            background.color = background.color == colors[index % max_colors] ? "transparent" : colors[index % max_colors]
                        }
                    }
                }
            }
        }

        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            legend.visible: false
            id: chart
            axes: [
                DateTimeAxis{
                    id: xAxis
                    labelsAngle: 270
                    format: "ddd hh:mm"
                },

                ValueAxis {
                    id: yAxis
                }
            ]
        }
    }
}


// import QtQuick 2.12
// import QtQuick.Controls 2.5
// import QtQuick.Controls.Material 2.12

// import QtQml 2.12
// import QtQuick.Layouts 1.12
// import QtCharts 2.12
// // import QtGraphicalEffects 1.12
// import Qt5Compat.GraphicalEffects

// Page {
//     property string unit : "ml"
//     property int partyId: partyController.ui_current_party_id
//     property var drinks : drinkProvider.getUIDrinksList(partyId)
// //    property date partyStarted: partyController.ui_current_party_started
//     property date partyEnded

//     Component.onCompleted: {
//         console.log("Party statistics onCompleted series 0 " + chartView.series(0))
//         plotter.setSeries(chartView.series(0), chartView.series(2), chartView.series(4), chartView.series(6))
//         plotter.setAxes(axisX, axisY1)
//         drinks = drinkProvider.getUIDrinksList(partyId)
//         plotter.update(partyId)
//     }

//     Connections {
//         target: partyController
//         function onUi_drinksChanged()
//         {
//             console.log("Drinks changed in party statistics view. party Id " + partyId)
//             plotter.setSeries(chartView.series(0), chartView.series(2), chartView.series(4), chartView.series(6))
//             plotter.setAxes(axisX, axisY1)
//             drinks = drinkProvider.getUIDrinksList(partyId)
//             plotter.update(partyId)
//         }
//     }

//     ConfirmationDialog {
//         id: deleteDrinkConfirmationDialog
//         standardButtons: Dialog.Ok | Dialog.Cancel
//     }

//     ScrollView {
//         anchors.fill: parent

//         Rectangle {
//             anchors.fill: parent
//             color: "transparent"

//             Column {
//                 anchors.horizontalCenter: parent.horizontalCenter
//                 spacing: 10

//                 width: parent.width

//                 ChartView {
//                     height: 400
//                     width: parent.width
//                     id: chartView
//                     antialiasing: true

//                     ValueAxis {
//                         id: axisY1
//                     }

//                     DateTimeAxis{
//                         id: axisX
//                         labelsAngle: 270
//                         format: "ddd hh:mm"
//                     }

//                     ScatterSeries {
//                         name: qsTr("Party start / end")
//                         axisX: axisX
//                         axisY: axisY1
//                         id: partyStart
//                         color: "green"
//                         pointsVisible: true
//                         markerSize: 20
//                     }

//                     //CONSUMPTION 1
//                     AreaSeries {
//                         name: qsTr("Consumption (") + unit + ")"
//                         axisX: axisX
//                         axisY: axisY1
//                         upperSeries: consumption1
//                         color: "#f5a742"
//                     }

//                     LineSeries {
//                         axisX: axisX
//                         axisY: axisY1
//                         id: consumption1
//                         color: "#f57542"
//                         width: 2
//                     }
//                     //CONSUMPTION 2
//                     AreaSeries {
//                         name: qsTr("Consumption (") + unit + ")"
//                         axisX: axisX
//                         axisY: axisY1
//                         upperSeries: consumption2
//                         color: "#4299f5"
//                     }

//                     LineSeries {
//                         axisX: axisX
//                         axisY: axisY1
//                         id: consumption2
//                         color: "#057bf7"
//                         width: 2
//                     }
//                     //CONSUMPTION 3
//                     AreaSeries {
//                         name: qsTr("Consumption (") + unit + ")"
//                         axisX: axisX
//                         axisY: axisY1
//                         upperSeries: consumption3
//                         color: "#dce673"
//                     }

//                     LineSeries {
//                         axisX: axisX
//                         axisY: axisY1
//                         id: consumption3
//                         color: "#95a300"
//                         width: 2
//                     }

//                 }

//                 ListView {
//                     id: drinksList
//                     height: 200
//                     width: parent.width
//                     clip: true
//                     model: drinks
//                     delegate: drinkTypeDelegate
//                     spacing: 5
//                 }

//                 Component {
//                     id: drinkTypeDelegate

//                     Rectangle {
//                         width: drinksList.width
//                         height: 40

//                         Text {
//                             anchors.left: parent.left
//                             font.pixelSize: 10
//                             text: drinkController.type(modelData.ui_drink_type_id) + " " + modelData.ui_amount_ml + " " + unit + " (" + modelData.ui_timestamp + ")"
//                         }

//                         Button {
//                             focusPolicy: Qt.NoFocus
//                             anchors.right: parent.right
//                             text: "X"
//                             onClicked: {
//                                 deleteDrinkConfirmationDialog.openDialog(qsTr("Delete the drink?"))
//                                 deleteDrinkConfirmationDialog.accepted.connect(function(){
//                                     console.log("DELETE drink")
//                                     partyController.deleteDrink(modelData.ui_id)
//                                 })
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
