import QtQuick
import QtQuick.Controls

Item {
    Rectangle {
        anchors.fill: parent
        color: "#333"

        Rectangle {
            width: parent.width * (dashboardManager.fuelLevel / 100)
            height: parent.height
            color: dashboardManager.fuelLevel < 20 ? "red" : "green"
        }

        Text {
            anchors.centerIn: parent
            text: dashboardManager.fuelLevel + "%"
            color: "white"
            font.pixelSize: 24
        }
    }
}
