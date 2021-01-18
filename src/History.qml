import QtQuick 2.0


GridView {

    id: root

    cellHeight: root.height/4
    cellWidth: root.width/4
    clip: true

    delegate: Item {
        id: _delegete
        height: root.height/4
        width: root.width/4
        property var my_margin: 10

        Column {
            id: _delegete__col
            height: parent.height-my_margin
            width: parent.width-my_margin
            x: my_margin/2
            y: my_margin/2

            Image {
                source: "file:" + display.screenshot_path
                height: parent.height-15
                width: parent.width
                fillMode: Image.PreserveAspectFit
            }
            Text {
                text: display.simular_procent + "%"
                height: 15
                width: parent.width
                wrapMode: Text.WrapAnywhere
                font {
                    pointSize: 12
                }
                horizontalAlignment: Text.AlignHCenter
            }
        }

        MouseArea {
            id: mouse_area1
            z: 1
            hoverEnabled: false
            anchors.fill: parent
            onClicked: {
                root.currentIndex = index
            }
         }
    }




}

