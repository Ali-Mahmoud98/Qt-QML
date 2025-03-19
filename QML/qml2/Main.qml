import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Image {
        id: img_1
        x: 44
        y: 37
        source: "https://www.ultralibrarian.com/wp-content/uploads/2022/06/shutterstock_13717364781.jpg"
        z: 0
        anchors.verticalCenterOffset: -1
        anchors.horizontalCenterOffset: 5
        anchors.centerIn: parent
        width: 564
        height: 406
    }
}
