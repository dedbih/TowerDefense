import QtQuick
import QtQuick.Controls

Window {
    id: window2
    width: 520
    height: 480
    visible: true
    title: qsTr("TowerDefense")

    property int filas: 10
    property int columnas: 10

    Grid {
        id: matriz
        rows: filas
        columns: columnas
        spacing: 1
        anchors.centerIn: parent

        Repeater {
            model: filas * columnas

            Rectangle {
                width: 25
                height: 25
                border.color: "black"

                // Índices
                property int row: Math.floor(index / columnas)
                property int col: index % columnas
                property int value: gridData[index]

                color: {
                    if (value === 0) return "green"
                    else if (value === 1) return "red"
                    else if (value === 2) return "blue"
                    else if (value === 3) return "white"
                }
            }
        }
    }
}

