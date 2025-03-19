import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id: myShape
        width: 100
        height: width
        color: "orange"

        function update() {
            console.log(x ," x ", y)
            lable.text = Math.round(x) + " x " + Math.round(y)
        }

        x:100
        y:100
        onXChanged: update()
        onYChanged: update()
        // anchors.centerIn: parent

        Component.onCompleted: update()

        Text {
            id: lable
            text: qsTr("text")
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }
    }
}
