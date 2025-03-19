import QtQuick
import QtQuick.Controls

Item {
    id: speedometer

    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            // Background
            ctx.beginPath();
            ctx.fillStyle = "#333";
            ctx.arc(width/2, height/2, Math.min(width, height)/2 - 10, 0, Math.PI * 2);
            ctx.fill();

            // Speed arc
            ctx.beginPath();
            ctx.lineWidth = 30;
            ctx.strokeStyle = "#555";
            ctx.arc(width/2, height/2, Math.min(width, height)/2 - 50, Math.PI * 0.7, Math.PI * 0.3);
            ctx.stroke();

            // Active speed arc
            ctx.beginPath();
            ctx.lineWidth = 30;
            ctx.strokeStyle = "#00ff00";
            var speedRatio = Math.min(dashboardManager.currentSpeed / 220, 1);
            ctx.arc(width/2, height/2, Math.min(width, height)/2 - 50,
                    Math.PI * 0.7,
                    Math.PI * 0.7 + speedRatio * Math.PI * 0.6);
            ctx.stroke();
        }
    }

    Text {
        anchors.centerIn: parent
        text: dashboardManager.currentSpeed
        font.pixelSize: 92
        color: "white"
    }

    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.verticalCenter
            topMargin: 100
        }
        text: "km/h"
        font.pixelSize: 24
        color: "gray"
    }
}
