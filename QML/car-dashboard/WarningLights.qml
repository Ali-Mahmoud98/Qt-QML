import QtQuick
import QtQuick.Controls

Item {
    Rectangle {
        anchors.fill: parent
        color: "#222"

        Rectangle {
            width: 50
            height: 50
            anchors.centerIn: parent
            color: dashboardManager.engineWarning ? "red" : "gray"
            radius: 25

            Text {
                anchors.centerIn: parent
                text: "ENG"
                color: "white"
                font.pixelSize: 14
            }
        }
    }
}
