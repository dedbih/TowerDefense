import QtQuick

Window {
    id: window2
    width: 1039
    height: 675
    visible: true
    title: qsTr("TowerDefense")

    Grid {
        id: matriz
        rows: 26
        columns: 40
        spacing: 1
        anchors.centerIn: parent

        Instantiator {
            id : gridmachine
            model: 1040 // number of elements needed, fills up 40*26 squares
            delegate: Rectangle {
                width: 25
                height: 25
                color: "green"
                border.color: "black"
                property int row : Math.floor(index/40) // calculates which row the block is in dividing index by number of columns
                property int col : index % 40 //calculates which column the block is in by dividing index by number of columns
                objectName: "block" + row + "_" + col

                Text {
                            anchors.centerIn: parent
                            text: index  // function automatically asigns numbers when creating each object (0 to model-1)
                        }
            }

            onObjectAdded: (index, object) => { //sets each object's parent as matriz after creation, the grid automatically puts each object in order
                            object.parent = matriz
                        }

        }


    }

}
