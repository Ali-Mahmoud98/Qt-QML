import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property int middle: (height / 2) - 50

    MyButton {
        id: button1
        x: 100
        y: middle

        color: "red"
        clickColor: "yellow"
        title: "Button1"
    }

    MyButton {
        id: button2
        x: (parent.width / 2) - (width / 2)
        y: middle

        color: "green"
        clickColor: "blue"
        title: "Button2"
    }

    MyButton {
        id: button3
        x: parent.width - 200
        y: middle

        color: "#a3e8a3"
        clickColor: "#494989"
        title: "Button3<br>Testing!"
    }

    MyButton {
        id: button4
        x: (parent.width / 2) - (width / 2)
        y: middle + 120
        width: 450

        color: "#a308a3"
        clickColor: "#424989"
        title: "<b>Super</b> <b>Long</b> <b>Button</b>"
    }
}
