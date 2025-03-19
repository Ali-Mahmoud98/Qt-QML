import QtQuick

Item {
    // item is a non visual element, it does not things like color
    id: root
    width: 100
    height: 100
    property color color: "#FF0AAF"
    property color clickColor: "green"
    property string title: "Click Me"

    Rectangle {
        id: myRec
        anchors.fill: parent
        color: root.color

        Text {
            id: display
            text: root.title
            anchors.centerIn: parent
        }

        MouseArea {
            id: mouse_area
            anchors.fill: parent
            onPressed: parent.color = root.clickColor
            onReleased: parent.color = root.color
        }
    }
}
