import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
//import QtCharts 2.12

import "qrc:/"
import DrinQ 1.0

Item {
    property string unit : "ml"

    Rectangle {
        anchors.fill: parent
        color: "palegreen"

        Column {
            anchors.centerIn: parent
            spacing: 30

//            CustomChart {
//                id: customChart
//                width: 100; height: 100
//                name: "A simple pie chart"
//                color: "red"
//            }

//            ChartView {
//                title: "Line"
//                anchors.fill: parent
//                antialiasing: true

//                LineSeries {
//                    name: "LineSeries"
//                    XYPoint { x: 0; y: 0 }
//                    XYPoint { x: 1.1; y: 2.1 }
//                    XYPoint { x: 1.9; y: 3.3 }
//                    XYPoint { x: 2.1; y: 2.1 }
//                    XYPoint { x: 2.9; y: 4.9 }
//                    XYPoint { x: 3.4; y: 3.0 }
//                    XYPoint { x: 4.1; y: 3.3 }
//                }
//            }

        }
    }
}

