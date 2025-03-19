// import QtQuick
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        id: elTxt1
        text: qsTr("Hello From elTxt1")
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 25
        anchors.verticalCenterOffset: -109
        anchors.horizontalCenterOffset: 0
    }
    Text {
        id: elTxt2
        width: 123
        height: 21
        text: qsTr("Hello From elTxt2")
        anchors.verticalCenterOffset: 65
        anchors.horizontalCenterOffset: 1
        anchors.centerIn: parent
    }

    Switch {
        id: _switch
        x: 82
        y: 389
        text: qsTr("Switch")
    }

    Dial {
        id: dial
        x: 485
        y: 348
    }
}
