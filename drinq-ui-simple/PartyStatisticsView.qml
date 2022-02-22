import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.12

import "qrc:/"
import DrinQ 1.0


//import QtQuick 2.5
//import QtQuick.Particles 2.0

//Rectangle {
//    id: root
////    width: 480; height: 160
//    color: "#1f1f1f"

//    ParticleSystem {
//        id: particleSystem
//    }

//    Emitter {
//        id: emitter
//        anchors.centerIn: parent
//        width: 160; height: 80
//        system: particleSystem
//        emitRate: 10
//        lifeSpan: 1000
//        lifeSpanVariation: 500
//        size: 16
//        endSize: 32
//    }

////    Emitter {
////            id: emitter
////            anchors.left: parent.left
////            anchors.verticalCenter: parent.verticalCenter
////            width: 1; height: 1
////            system: particleSystem
////            emitRate: 10
////            lifeSpan: 6400
////            lifeSpanVariation: 400
////            size: 32
////            velocity: AngleDirection {
////                angle: -45
////                angleVariation: 0
////                magnitude: 100
////            }
////            acceleration: AngleDirection {
////                angle: 90
////                magnitude: 25
////            }
////        }

//    ImageParticle {
//        source: "football.png"
//        system: particleSystem

//        rotation: 15
//        rotationVariation: 5
//        rotationVelocity: 45
//        rotationVelocityVariation: 15

//    }
//}


Item {
    property string unit : "ml"

    Component.onCompleted: {
        partyController.update(chartView.series(0))
    }

    Rectangle {
        anchors.fill: parent
        color: "palegreen"

        Column {
            anchors.fill: parent
            spacing: 30

            //            CustomChart {
            //                id: customChart
            //                width: 100; height: 100
            //                name: "A simple pie chart"
            //                color: "red"
            //            }

            ChartView {
                height: 500
                width: 500
                id: chartView
                title: "Line"
//                anchors.fill: parent
                antialiasing: true

                ValueAxis {
                    id: axisY1
                    min: 0
                    max: 1000 /*partyController.ui_plot_max_value() + 10*/
                }

                DateTimeAxis{
                    id: axisX
                    min: partyController.plot_min()
                    max: partyController.plot_max()
                    labelsAngle: 270
                    format: "ddd hh:mm"
                }


                LineSeries {
                    name: "LineSeries"
                    axisX: axisX
                    axisY: axisY1
                    //                    XYPoint { x: 0; y: 0 }
                    //                    XYPoint { x: 1.1; y: 2.1 }
                    //                    XYPoint { x: 1.9; y: 3.3 }
//                    XYPoint { x: 2.1; y: 2.1 }
//                    XYPoint { x: 2.9; y: 4.9 }
                    //                    XYPoint { x: 3.4; y: 3.0 }
                    //                    XYPoint { x: 4.1; y: 3.3 }
                }
            }

            Button {
                height: 40
                width: 100
                text: "Update"
                onClicked: {
                    partyController.update(chartView.series(0))
                }
            }
        }
    }
}

