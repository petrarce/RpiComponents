import QtQuick 2.0
import QtQuick.Controls 1.4
import Thunder 0.1

Rectangle {
    width: 500
    height:500
    color: "lightblue"
    resources: RpiConnector {
        id: connection
        remoteAddress: "raspberrypi"
        port: 51525
        action: 2
        value: slider.value
        onValueChanged: send()
    }

    Button {
        id: reconnect
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Connect"
        width: 100
        height: 20
        onClicked: connection.reconnect()
    }

    Slider {
        id: slider
        anchors.bottom: reconnect.top
        width: parent.width
        height: 20
        minimumValue: -90
        maximumValue: 90
    }
}
