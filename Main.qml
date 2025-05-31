import QtQuick
import QtQuick.Controls

Window {
    id: window1
    width: 1200  // Aumentado para dar espacio al panel lateral
    height: 520
    visible: true
    title: qsTr("TowerDefense")

    property int filas: 16
    property int columnas: 32

    Row {
        anchors.fill: parent
        spacing: 10

        // Panel principal del grid
        Rectangle {
            width: 940
            height: parent.height
            color: "transparent"

            Grid {
                id: matriz
                rows: filas
                columns: columnas
                spacing: 1
                anchors.centerIn: parent

                Repeater {
                    model: pathFinder ? pathFinder.gridData : []

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

            // Botones de pathfinding en la parte inferior del grid
            Button {
                id: findPathButton
                text: "Encontrar Ruta"
                anchors.bottom: moveButton.top
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (pathFinder) pathFinder.findPath();
                }
            }

        }

        // Panel lateral para control de torres
        Rectangle {
            width: 240
            height: parent.height
            border.color: "black"
            border.width: 2

            ScrollView {
                anchors.fill: parent
                anchors.margins: 10
                clip: true

                Column {
                    width: parent.width - 20
                    spacing: 15

                    Text {
                        text: " CONTROL DE TORRES"
                        font.bold: true
                        font.pixelSize: 16
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        width: parent.width
                        height: 2
                        color: "#34495e"
                    }


                    // Sección de selección de torres
                    Column {
                        width: parent.width
                        spacing: 10

                        Text {
                            text: " SELECCIONAR TORRE"
                            font.bold: true
                            font.pixelSize: 14
                        }

                        Button {
                            text: " Artillero"
                            width: parent.width
                            height: 40
                            highlighted: pathFinder ? pathFinder.selectedTowerType === 11 : false
                            onClicked: {
                                if (pathFinder) pathFinder.selectedTowerType = 11;
                            }
                        }

                        Button {
                            text: " Arquero"
                            width: parent.width
                            height: 40
                            highlighted: pathFinder ? pathFinder.selectedTowerType === 14 : false
                            onClicked: {
                                if (pathFinder) pathFinder.selectedTowerType = 14;
                            }
                        }

                        Button {
                            text: " Mago"
                            width: parent.width
                            height: 40
                            highlighted: pathFinder ? pathFinder.selectedTowerType === 17 : false
                            onClicked: {
                                if (pathFinder) pathFinder.selectedTowerType = 17;
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 2
                    }

                    // Sección de colocación
                    Column {
                        width: parent.width
                        spacing: 10

                        Text {
                            text: " COLOCAR TORRE"
                            font.bold: true
                            font.pixelSize: 14
                            color: "#34495e"
                        }

                        Text {
                            text: "Posición (fila, columna):"
                            font.pixelSize: 12
                        }

                        TextField {
                            id: positionInput
                            width: parent.width
                            placeholderText: "Ej: 5,10"
                            font.pixelSize: 12

                            onAccepted: {
                                placeTowerFromInput()
                            }
                        }

                        Button {
                            text: " Colocar Torre"
                            width: parent.width
                            height: 35
                            enabled: pathFinder ? (pathFinder.selectedTowerType > 0 && positionInput.text.length > 0) : false
                            onClicked: {
                                placeTowerFromInput()
                            }
                        }

                        Text {
                            text: "Torre: " + getTowerName()
                            font.pixelSize: 11
                            wrapMode: Text.WordWrap
                            width: parent.width
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 2
                    }

                    // Sección de mejora
                    Column {
                        width: parent.width
                        spacing: 10

                        Text {
                            text: " MEJORAR TORRE"
                            font.bold: true
                            font.pixelSize: 14
                        }

                        Text {
                            text: "Posición de la torre (fila, columna):"
                            font.pixelSize: 12
                        }

                        TextField {
                            id: upgradePositionInput
                            width: parent.width
                            placeholderText: "Ejemplo: 5,10"
                            font.pixelSize: 12

                            onAccepted: {
                                upgradeTowerFromInput()
                            }
                        }

                        Button {
                            text: " Mejorar al siguiente nivel"
                            width: parent.width
                            height: 35
                            onClicked: {
                                upgradeTowerFromInput()
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 2
                    }

                    // Información adicional
                    Column {
                        width: parent.width
                        spacing: 5

                        Text {
                            text: " Estadisticas"
                            font.bold: true
                            font.pixelSize: 14
                        }

                        Text {
                            text: "..."
                            font.pixelSize: 10
                            wrapMode: Text.WordWrap
                            width: parent.width
                        }
                    }
                    // Sección de oleadas
                    Column {
                        width: parent.width
                        spacing: 10

                        Text {
                            text: " OLEADAS"
                            font.bold: true
                            font.pixelSize: 14
                        }

                        Button {
                            text: " Iniciar Oleada"
                            width: parent.width
                            height: 35
                            enabled: pathFinder ? !pathFinder.hayOleadaActiva() : false
                            onClicked: {
                                if (pathFinder) pathFinder.iniciarOleada();
                            }
                        }
                    }
                }
            }
        }
    }

    // Funciones auxiliares
    function placeTowerFromInput() {
        if (!pathFinder) return;

        var parts = positionInput.text.split(",");
        if (parts.length === 2) {
            var row = parseInt(parts[0].trim());
            var col = parseInt(parts[1].trim());

            if (pathFinder.placeTower(row, col)) {
                positionInput.text = ""; // Limpiar el campo si se colocó exitosamente
            }
        }
    }

    function upgradeTowerFromInput() {
        if (!pathFinder) return;

        var parts = upgradePositionInput.text.split(",");
        if (parts.length === 2) {
            var row = parseInt(parts[0].trim());
            var col = parseInt(parts[1].trim());

            if (pathFinder.upgradeTower(row, col)) {
                upgradePositionInput.text = ""; // Limpiar el campo si se mejoró exitosamente
            }
        }
    }

    function getTowerName() {
        if (!pathFinder) return "Ninguna";

        switch(pathFinder.selectedTowerType) {
            case 11: return "Artillero (Nivel 1)";
            case 14: return "Arquero (Nivel 1)";
            case 17: return "Mago (Nivel 1)";
            default: return "Ninguna";
        }
    }
}
