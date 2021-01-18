import QtQuick 2.0
import Backend 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ColumnLayout {

    id: root
    spacing: 0

    Backend_obj {
        id: _backend_obj
    }


    Rectangle {

        Layout.preferredHeight: root.height-_bottom_panel.Layout.preferredHeight
        Layout.fillWidth: true

        History {
            id: _history_qml
            anchors.fill: parent
        }
    }

    Rectangle {

        id: _bottom_panel

        Layout.preferredHeight: 40
        Layout.fillWidth: true

        Button {
            text: "Start"

            anchors.centerIn: parent
            height: 30

            MouseArea {
                z: 1
                hoverEnabled: false
                anchors.fill: parent
                onClicked: {
                    parent.text = _backend_obj.pressPause()
                }
            }
        }
    }

    Component.onCompleted: {
        _history_qml.model =  _backend_obj.getHistoryModel();
    }

}
