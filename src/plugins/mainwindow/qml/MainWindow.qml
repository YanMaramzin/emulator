import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CoreModels 1.0

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true
    topPadding: 0
    title: "Plugin System Example"

    header: ToolBar {
        id: bar

        Repeater {
            model: TabsModel
            ToolButton {
                text: model.title
            }
        }
    }

    StackLayout {
        id: stack
        anchors.fill: parent
        currentIndex: bar.currentIndex
        Repeater {
            model: TabsModel
            Loader {
                source: model.url
            }
        }
    }
    
    Component.onCompleted: {
        console.log("MainWindow loaded")
    }
}
