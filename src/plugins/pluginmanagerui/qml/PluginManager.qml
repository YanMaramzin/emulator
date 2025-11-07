import QtQuick
import QtQuick.Controls
import CoreModels 1.0


Page {
    id: root
    anchors.fill: parent

    // PluginManagerBackend {
    //     id: backend
    // }

    // Rectangle {
    //
    // }

    ListView {
        anchors.fill: parent
        model: PluginListModel

        delegate: Rectangle {
            height: 40
            width: 40
            color: "red"

            Text {
                anchors.centerIn: parent
                text: "PLUGIN" + modelData
            }
        }
    }

    Component.onCompleted: {
        console.log("PluginManager loaded")
    }
}