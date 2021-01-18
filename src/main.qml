import QtQuick 2.12
import QtQuick.Window 2.12
import Backend 1.0


Window {
    id: root
    visible: true

    minimumHeight: 480
    minimumWidth: 640
    title: qsTr("deefscreen")


    Backend {
        anchors.fill: parent
        anchors.margins: 5
    }
}
