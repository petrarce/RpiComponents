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
        value: 0
        onValueChanged: send()
        property int wheelState: 0
        onWheelStateChanged: {
            switch(wheelState)
            {
            case -1:
                connection.action = 2;
                connection.value = -90;
                break;
            case 0:
                connection.action = 2;
                connection.value = 0;
                break;
            case 1:
                connection.action = 2;
                connection.value = 90;
                break;
            default:
                return;
            }
            send()
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
    focus: true
    Keys.onLeftPressed: {
        connection.wheelState = -1
    }
    Keys.onRightPressed: {
        connection.wheelState = 1
    }
    Keys.onReleased: {
        if(event.isAutoRepeat)
            return;
        switch(event.key)
        {
        case Qt.Key_Left:
        case Qt.Key_Right:
            connection.wheelState = 0
            console.log("key released is triggered")
            break;
        default:
        }
    }
    /*Slider {
        id: slider
        anchors.bottom: reconnect.top
        width: parent.width
        stepSize: 10
        height: 20
        minimumValue: -90
        maximumValue: 90
        focus: true
        Keys.onLeftPressed: {
            animationRight.stop()
            animationCenter.stop()
            animationLeft.start()
        }
        Keys.onRightPressed: {
            animationLeft.stop()
            animationCenter.stop()
            animationRight.start()
        }
        Keys.onReleased: {
            switch(event.key){
            case Qt.Key_Left:
            case Qt.Key_Right:
                animationLeft.stop();
                animationRight.stop();
                animationCenter.start();
            }
        }

        NumberAnimation on value {
            id: animationLeft
            from: slider.value
            to: -90
            duration:1000
            running: false
        }
        NumberAnimation on value {
            id: animationRight
            from: slider.value
            to: 90
            duration:1000
            running: false
        }
        NumberAnimation on value {
            id: animationCenter
            from: slider.value
            to: 0
            duration:1000
            running: false
        }
    }*/


}
