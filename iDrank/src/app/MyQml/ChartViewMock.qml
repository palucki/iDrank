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
    property int party_id : 1
    // property int partyId: partyController.ui_current_party_id
    // property var drinks : drinkProvider.getUIDrinksList(partyId)
//    property date partyStarted: partyController.ui_current_party_started
    // property date partyEnded 
    property string series_name : "line"
    property var colors : ["#ffd275", "#a57f60", "#e3a587", "#db5a42", "#e8ae68", "#f4ac32"]
    property int max_colors : colors.length
    property var users : party_controller.getUsersForParty(party_id)

    Component.onCompleted: {
        party_plotter.setAxes(xAxis, yAxis)
        
        for(var i = 0; i < users.length; i++)
        {
            party_plotter.addSeries(createSeries(users[i].ui_name, colors[i % max_colors]))
        }
        party_plotter.plot(party_id)
    }

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
