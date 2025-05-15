import QtQuick
import QtQuick.Controls

Window {
    id: window1
    width: 520
    height: 520
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
            model: pathFinder.gridData

            Rectangle {
                width: 25
                height: 25
                border.color: "black"

                property int value: modelData

                // Para 4 como color indicativo de la ruta, para 0, 1, 2 y 3 usamos imagenes
                color: {
                    if (value === 4) return "yellow"; // Ruta marcada
                    return "transparent";
                }

                Image {
                    anchors.fill: parent
                    visible: (value === 2 || value === 3 || value === 0 || value === 1)
                    source: value === 2 ? "asset/images/ELF.png"
                            : value === 3 ? "asset/images/OGRO.png"
                            : value === 0 ? "asset/images/PASTO.png"
                            : value === 1 ? "asset/images/TIERRA.png"
                            : ""
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }
            }
        }
    }

    Button {
        id: findPathButton
        text: "Encontrar Ruta"
        anchors.bottom: moveButton.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            pathFinder.findPath();
        }
    }

    Button {
        id: moveButton
        text: "Mover Personaje"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: !pathFinder.isMoving
        onClicked: {
            pathFinder.moveCharacter();
        }
    }
}

