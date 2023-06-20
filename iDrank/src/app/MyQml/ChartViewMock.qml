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
    // property int partyId: partyController.ui_current_party_id
    // property var drinks : drinkProvider.getUIDrinksList(partyId)
//    property date partyStarted: partyController.ui_current_party_started
    // property date partyEnded 
    property string series_name : "line"
    property int users_count : 5

    Component.onCompleted: {
        party_plotter.setAxes(xAxis, yAxis)
        for(var i = 1; i <= party_plotter.numberOfUsers(1); i++)
        {
            party_plotter.addSeries(createSerie("alko" + i))
        }
        // party_plotter.plot(1)
    }

    function createSerie(name) {
        var series = chart.createSeries(ChartView.SeriesTypeLine, name, xAxis, yAxis);
        series.pointsVisible = true;
        series.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        var pointsCount = Math.round(Math.random() * 20);
        var x = 0.0;
        for(var j = 0; j < pointsCount; j ++) {
            x += (Math.random() * 2.0);
            var y = (Math.random() * 10.0);
            series.append(x, y);
        }

        return series
    }

    function createSeries(names) {
        for(var i = 0; i < names.length; i++) {
            console.log("Adding series " + names[i])
            createSerie(names[i])
        }
    }

    function addLineSeries() {
        console.log("addLineSeries")
        var series = chart.createSeries(ChartView.SeriesTypeLine, "line", xAxis, yAxis);
        series.pointsVisible = true;
        series.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        series.name = series_name + chart.count
        console.log("Series name " + series.name)
        // series.hovered.connect(function(point, state){ console.log(point); }); // connect onHovered signal to a function
        var pointsCount = Math.round(Math.random()* 20);
        var x = 0.0;
        for(var j = 0;j < pointsCount;j ++) {
            x += (Math.random() * 2.0);
            var y = (Math.random() * 10.0);
            series.append(x, y);
        }
    }

    function removeOneSeries() {
        console.log("removeOneSeries number " + chart.count)
        var series = chart.series(series_name + chart.count)
        console.log(series)
        if(series) {
            chart.removeSeries(series)
        }
    }

    function removeAllSeries() {
        chart.removeAllSeries()
    }

    ColumnLayout {
        id: layoutRoot
        anchors.fill: parent

        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: chart
            axes: [
                ValueAxis{
                    id: xAxis
                    min: 1.0
                    max: 10.0
                },
                ValueAxis{
                    id: yAxis
                    min: 0.0
                    max: 10.0
                }
            ]
        }

        RowLayout {
            Layout.maximumHeight: 50
            Rectangle {
                color: "darkseagreen"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Create series"
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: createSeries(["Puza", "Fuki", "Kozik", "Jonasz"])
                }
            }
            Rectangle {
                color: "darkseagreen"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "Add"
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: addLineSeries()
                }
            }
            Rectangle {
                color: "tomato";
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    text: "Remove"
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: removeOneSeries()
                }
            }

            Rectangle {
                color: "tomato";
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    text: "Remove All"
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: removeAllSeries()
                }
            }
        }
    }
    
    // GridLayout { 
    //     rows: 2
    //     columns: 2
    //     anchors.fill: parent
        // }

}
