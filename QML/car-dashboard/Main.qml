import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Particles

ApplicationWindow {
    visible: true
    width: 1024
    height: 600
    title: "Car Dashboard"

    // Animated background with particle and gradient effects
    Rectangle {
        id: backgroundRoot
        anchors.fill: parent

        // Gradient background that animates
        gradient: Gradient {
            GradientStop {
                id: topGradientStop
                position: 0
                color: "#1A1A2E"
            }
            GradientStop {
                id: bottomGradientStop
                position: 1
                color: "#16213E"
            }
        }

        // Animated color transitions
        SequentialAnimation {
            running: true
            loops: Animation.Infinite

            ColorAnimation {
                target: topGradientStop
                property: "color"
                to: "#0F3460"
                duration: 5000
            }
            ColorAnimation {
                target: bottomGradientStop
                property: "color"
                to: "#212121"
                duration: 5000
            }
            ColorAnimation {
                target: topGradientStop
                property: "color"
                to: "#1A1A2E"
                duration: 5000
            }
            ColorAnimation {
                target: bottomGradientStop
                property: "color"
                to: "#16213E"
                duration: 5000
            }
        }

        // Particle system for subtle background movement
        ParticleSystem {
            id: particleSystem
            anchors.fill: parent

            ImageParticle {
                source: "particle.png"
                color: "#30FFFFFF"
                colorVariation: 0.3
                rotation: 0
                rotationVariation: 360
                entryEffect: ImageParticle.Scale
            }

            Emitter {
                width: parent.width
                height: parent.height
                anchors.fill: parent
                system: particleSystem

                emitRate: 20
                lifeSpan: 6000

                velocity: PointDirection {
                    x: -10
                    y: 20
                    xVariation: 10
                    yVariation: 10
                }

                size: 10
                sizeVariation: 20
            }
        }

        // Subtle grid overlay
        Canvas {
            anchors.fill: parent
            opacity: 0.1

            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                ctx.strokeStyle = "rgba(255,255,255,0.05)";
                ctx.lineWidth = 1;

                // Vertical lines
                for (var x = 0; x < width; x += 50) {
                    ctx.beginPath();
                    ctx.moveTo(x, 0);
                    ctx.lineTo(x, height);
                    ctx.stroke();
                }

                // Horizontal lines
                for (var y = 0; y < height; y += 50) {
                    ctx.beginPath();
                    ctx.moveTo(0, y);
                    ctx.lineTo(width, y);
                    ctx.stroke();
                }
            }
        }

        // Main dashboard content
        RowLayout {
            anchors.fill: parent
            spacing: 20

            // Left Side - Warning Lights and Gear
            ColumnLayout {
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.2

                WarningLights {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height * 0.3
                }

                Text {
                    text: dashboardManager.currentGear
                    font.pixelSize: 48
                    color: "white"
                    Layout.alignment: Qt.AlignCenter
                }
            }

            // Center - Speedometer
            Speedometer {
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.5
            }

            // Right Side - Fuel and Navigation
            ColumnLayout {
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.3

                FuelGauge {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height * 0.3
                }

                NavigationDisplay {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}
