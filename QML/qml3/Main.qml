import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Image {
        id: img_1
        source: "https://variwiki.com/images/archive/4/4e/20211220183943%21Qt_logo.png"
        width: parent.width / 2
        height: parent.height / 2
        anchors.centerIn: parent
        opacity: 0.25
    }

    TextInput {
        id: input_1
        text: "Hello World !!"
        // Start Positioning
        anchors.centerIn: parent
        // x: 30
        // y: 100
        // End Positioning
        font.pixelSize: 25
    }

    Text {
        id: txt_1
        text: input_1.text // this is called property binding.
        font.pixelSize: 25
    }

    Rectangle {
        id: rectangle
        // start position of the Rectangle
        x: 20
        y: 134
        // end position of the Rectangle
        width: 125
        height: 51
        color: "red"
        radius: 10
        border.width: 2
        // opacity: 0.5, try use "z"
        // try1 -> the blue Rectangle will appear above red Rectangle
        // z: 1
        // try2
        z: 2
    }

    Rectangle {
        id: rectangle1
        // start position of the Rectangle
        x: 5
        y: 168
        // end position of the Rectangle
        width: 120
        height: 47
        color: "blue"
        radius: 10
        border.width: 2
        // opacity: 0.5
        // try1 -> the blue Rectangle will appear above red Rectangle
        // z: 2
        // try2
        z: 1
    }
}
