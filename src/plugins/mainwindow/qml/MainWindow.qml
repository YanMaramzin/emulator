import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true
    title: "Main Window"

    Rectangle {
        anchors.fill: parent
        color: "#d71b1b"

        Text {
            anchors.centerIn: parent
            text: qsTr("Hello from QtUIPlugin")
            color: "white"
            font.pixelSize: 24
        }
    }
}
