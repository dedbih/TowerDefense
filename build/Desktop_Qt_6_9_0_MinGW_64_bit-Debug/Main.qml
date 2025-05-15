import QtQuick

Window {
    id: window2
    width: 1030
    height: 675
    visible: true
    title: qsTr("TowerDefense")

    Image {
        id: myImage
        source: "qrc:img/logn.jpg"
        width: parent.width
        height: parent.height
    }
}

