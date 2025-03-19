import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    // start example about TapHandler
    // Rectangle {
    //     id : rect1
    //     width: 100
    //     height: 100
    //     anchors.centerIn: parent

    //     color: input_handler.pressed ? "red" : "blue"

    //     TapHandler {
    //         id: input_handler
    //     }
    // }
    // end example about TapHandler

    // start type "item" -> non-vistual item class
    // Item {
    //     id: itm_1
    //     width: 200
    //     height: 200
    //     anchors.centerIn: parent

    //     Rectangle {
    //         id: rect_1
    //         color: "red"
    //         anchors.fill: parent
    //     }
    // }
    // end type "item"

    // start Rectangle
    Rectangle {
        id: rect_2
        anchors.centerIn: parent
        color: "red"
        width: 200
        height: 200
        border.color: "black"
        border.width: 3

        radius: width

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "red"
            }
            GradientStop {
                position: 1.0
                color: "blue"
            }
        }
    }
    // end Rectangle
}
