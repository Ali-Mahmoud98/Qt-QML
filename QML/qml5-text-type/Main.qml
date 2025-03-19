import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        id: txt1
        text: qsTr("<html>
        <b>Hello</b> <i><font color='green'>World</font></i>
        </html><br>
        <font color='#A15DF0'>This is a test</font><br>
        <a href='https://www.google.com/'>Visit Google</a>")
        anchors.centerIn: parent
        font.pixelSize: 25
        color: "orange"
        // linkColor: "black"

        // Link color control
        linkColor: hoveredLink ? "red" : "blue"  // Change colors here
        property string hoveredLink: ""

        // onLinkHovered: {
        //     hoveredLink = link  // Track which link is being hovered
        //     console.log("Hover on Link: "+ link)
        // }
        onLinkHovered: function(link) {
            hoveredLink = link;
            console.log("Hover on Link: " + link);
        }
        // onLinkActivated: Qt.openUrlExternally(link)
        onLinkActivated: function(link) {
            Qt.openUrlExternally(link);
        }
    }
}
