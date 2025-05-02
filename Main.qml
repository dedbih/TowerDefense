import QtQuick
import QtQuick.Controls

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("TowerDefense")

    Text {
    id: titulo
    text: qsTr("Tower Defense")
    anchors.top: parent.top
    anchors.topMargin: 15
    anchors.horizontalCenter: parent.horizontalCenter

    }
    Button {
        id: botonInicio
        text: qsTr("Iniciar")
        anchors.top: titulo.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            var component = Qt.createComponent("GameWindow.qml") // loads window file into memory
            if (component.status === Component.Ready) { //checks if the component was successfully loaded.
                var gameWindow = component.createObject(mainWindow) // creates an instance of the GameWindow, mainWindow is passed as parent, if it ends GameWindow ends too
                gameWindow.show()
            } else {
                console.log("Error loading GameWindow:", component.errorString())
            }
        }
    }
}
