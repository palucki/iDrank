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
    property var plotter;

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

    function updatePlot() {
        // plotter.reset()
        chart.removeAllSeries()
        plotter.setAxes(xAxis, yAxis)
        for(var i = 0; i < users.length; i++)
        {
            plotter.addSeries(createSeries(users[i].ui_name, colors[i % max_colors]))
        }
        plotter.plot(party_id)
    }

    Component.onCompleted: {
        console.log("party statistics for party id " + party_id + " users " + users.length)
        updatePlot()
    }

    Connections {
        target: party_controller
        function onUi_drinks_countChanged()
        {
            // this function is called only in case of current party - drink added / removed
            // that's why we need to fetch users if any was added 
            users = users_controller.getUsers()
            
            console.log("Drinks changed in party statistics view. party Id " + party_id)
            console.log("Removing all series")
            updatePlot()
            drinksList.model = party_controller.getDrinksForParty(party_id)
        }
    }

    Connections {
        target: users_controller
        function onUsers_changed() {
            users = users_controller.getUsers(true)
            console.log("party statitsics view users changed now size: " << users.length)
            updatePlot()
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
                            plotter.toggleVisibility(modelData.ui_name)
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

        ListView {
            id: drinksList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: party_controller.getDrinksForParty(party_id)
            delegate: drinkTypeDelegate
            spacing: 5
        }
    }

    ConfirmationDialog {
        id: deleteDrinkConfirmationDialog
        standardButtons: Dialog.Ok | Dialog.Cancel
    }

    Component {
        id: drinkTypeDelegate

        Rectangle {
            width: drinksList.width
            height: 40

            Text {
                anchors.left: parent.left
                font.pixelSize: 10
                text: drink_type_controller.type(modelData.ui_drink_type_id) + " " + modelData.ui_amount_ml + " ml (" + modelData.ui_timestamp + ")"
            }

            Button {
                visible: party_controller.isCurrentParty(party_id)
                focusPolicy: Qt.NoFocus
                anchors.right: parent.right
                text: "X"
                onClicked: {
                    deleteDrinkConfirmationDialog.openDialog(qsTr("Delete the drink?"))
                    deleteDrinkConfirmationDialog.accepted.connect(function(){
                        console.log("DELETE drink")
                        party_controller.removeDrink(modelData.ui_id)
                    })
                }
            }
        }
    }
}