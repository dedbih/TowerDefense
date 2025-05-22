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
                    visible: (value === 0 || value === 1 || value === 2 || value === 3 || value ===5
                              || value === 6 || value === 7 || value === 8 || value === 9 || value === 10
                              || value ===11 || value ===12 || value ===13 ||value ===14 || value===15
                              || value ===16 || value ===17 || value === 18 || value ===19)
                    source: value === 0 ? "asset/images/PASTO.png"
                            : value === 1 ? "asset/images/TIERRA.png"
                            : value === 2 ? "asset/images/ARP.png"
                            : value === 3 ? "asset/images/ARPM.png"
                            : value === 5 ? "asset/images/ELF.png"
                            : value === 6 ? "asset/images/ELFM.png"
                            : value === 7 ? "asset/images/OGRO.png"
                            : value === 8 ? "asset/images/OGROM.png"
                            : value === 9 ? "asset/images/MER.png"
                            : value === 10 ? "asset/images/MERM.png"
                            : value === 11 ? "asset/images/ART1.png"
                            : value === 12 ? "asset/images/ART2.png"
                            : value === 13 ? "asset/images/ART3.png"
                            : value === 14 ? "asset/images/ARQ1.png"
                            : value === 15 ? "asset/images/ARQ2.png"
                            : value === 16 ? "asset/images/ARQ3.png"
                            : value === 17 ? "asset/images/MAGO1.png"
                            : value === 18 ? "asset/images/MAGO2.png"
                            : value === 19 ? "asset/images/MAGO3.png"
                            : ""
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }
            }
        }
    }

    Button {
        id: findPathButton
        text: "Inicio"
        anchors.bottom: matriz.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            pathFinder.findPath();
        }
    }

}

