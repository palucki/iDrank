import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

import QtQml 2.12
import QtQuick.Layouts 1.12

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

            CustomChart {
                id: customChart
                width: 100; height: 100
                name: "A simple pie chart"
                color: "red"
            }
        }
    }
}

