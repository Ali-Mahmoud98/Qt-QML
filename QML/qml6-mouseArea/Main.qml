import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Rectangle {
        id: rectArea
        width: 200
        height: 200
        color: "blue"
        anchors.centerIn: parent

        MouseArea {
            id: myMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked: function(mouse) {
                console.log("Clicked: " + mouse.button)
                if(mouse.button === Qt.LeftButton) {
                    parent.color = "green"
                }
                if(mouse.button === Qt.RightButton) {
                    parent.color = "red"
                }
            }

            onDoubleClicked: function(mouse) {
                console.log("Double Clicked: " + mouse.button)
            }

            // you to turn hover on
            hoverEnabled: true
            // onPositionChanged: function(mouseX, mouseY) {
            //     console.log("Position X:" + mouseX + "Y:" + mouseY)
            // }
            onPositionChanged: console.log("Position X:" + mouseX + " Y:" + mouseY)
            onEntered: parent.color = "orange"
            onExited: parent.color = "blue"
        }
    }
}
