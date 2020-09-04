import QtQuick 2.0
import QtQuick.Controls 1.4
import Thunder 0.1

Rectangle {
    id: app
    
    focus: true
    width: 500
    height:500
    color: "lightblue"
    resources: [
        RpiConnector {
            id: connection
            remoteAddress: "raspberrypi"
            port: 51525
            action: 2
            value: 0
            property int wheelState: 0
            onWheelStateChanged: {
                connection.action = wheelState;
                send()
            }
        },
        ThunderDistanceListener {
            id: dist
            remoteAddress: connection.remoteAddress
            port: connection.port + 1
            onDistancesChanged: console.log(distances)
        }
    ]
    
    Repeater {
        model: 360
        delegate: Rectangle {
            width: 10
            height: 10
            radius: 5
            color: "red"
            property vector2d center: Qt.vector2d(Math.cos(index * Math.PI / 180),
                                Math.sin(index * Math.PI / 180)).times(dist.distances[index] * 10)
            onCenterChanged: console.log(center)
            x: center.x + app.width / 2
            y: center.y + app.height / 2
        }
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
    
    Keys.onUpPressed: connection.wheelState = RpiConnector.Forevard
    Keys.onDownPressed: connection.wheelState = RpiConnector.Backward
    Keys.onLeftPressed: connection.wheelState = RpiConnector.RotateLeft
    Keys.onRightPressed: connection.wheelState = RpiConnector.RotateRight
    Keys.onReleased: {
        if(event.isAutoRepeat)
            return;
        switch(event.key)
        {
        case Qt.Key_Up:
        case Qt.Key_Down:
        case Qt.Key_Left:
        case Qt.Key_Right:
            connection.wheelState = RpiConnector.Stop
            console.log("key released is triggered")
            break;
        default:
        }
    }
}
