import QtQuick 2.1
import PathExploration 0.1
import QtQuick.Controls 1.0

ApplicationWindow {
    visibility: ApplicationWindow.FullScreen
    Rectangle {
        id: scene

        property real sceneWidth: 500
        property real sceneHeight: 500
        property var objects: [
            { w: 100, l: 50, c: Qt.vector2d(0, 100)},
            { w: 200, l: 100, c: Qt.vector2d(450, 250)},
            { w: 50, l: 50, c: Qt.vector2d(20, 300)},
        ]
        property vector2d targetPoint: Qt.vector2d(0,0)
        anchors.fill: parent
        color: "lightblue"

        resources: [
            Environment {
                id: envi
                objects: scene.objects
                onObjectsChanged: obstaklesDraw.model = envi.objects
            },
            Robot {
                id: nvigatableRobot

                center: Qt.vector2d(scene.width / 2, scene.height/ 2)
                focus: true
                rotationStep: 5
                stepLength: 5
                onTargetPositionChanged: {
                    startAutopilot(envi.objects);
                }
                maxObstackleDist: 40
                autopilotSpeed: slider.value
            }
        ]

        Rectangle {
            id: targetPt
            width:10
            height: width
            x: scene.targetPoint.x - width/2
            y: scene.targetPoint.y - height/2
            radius: width/2
            color: "red"
        }

        //paint robot
        Rectangle {
            id: robot

            property real stepsize: 5
            property vector2d center: nvigatableRobot.center

            rotation: nvigatableRobot.rotation
            width: 2 * nvigatableRobot.maxObstackleDist / 3; height: width
            x: center.x - width / 2; y: center.y - height / 2
            color: "green"
            onRotationChanged: console.log("rotation:", rotation)


            Repeater{
                model: 4
                delegate: Rectangle {
                    property vector2d localOffsetDir: Qt.vector2d(Math.cos((index * 90) * Math.PI / 180),
                                                     Math.sin((index * 90) * Math.PI / 180))
                    property vector2d wsDirection: Qt.vector2d(Math.cos((robot.rotation + index * 90) * Math.PI / 180),
                                                          Math.sin((robot.rotation + index * 90) * Math.PI / 180))
                    property real offsLength: parent.width / 2 + width / 2

                    width: parent.width
                    height: width
                    x: localOffsetDir.x * offsLength
                    y: localOffsetDir.y * offsLength
                    onXChanged: console.log("x:", x, "y:", y, "offsLength:", offsLength, "localOffsetDir:", localOffsetDir, "width:", width, "height:", height)
                    onYChanged: console.log("x:", x, "y:", y, "offsLength:", offsLength, "localOffsetDir:", localOffsetDir, "width:", width, "height:", height)
                    color: "transparent"
                    border.width: 2
                    border.color: (envi.hasObstackle(robot.center,
                                                    wsDirection,
                                                    nvigatableRobot.maxObstackleDist))? "red":"green"
                }
            }

            Rectangle {
                id: nose

                width: parent.width/5
                height: width
                anchors.left: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }


        //paint obstackles
        Repeater{
            id: obstaklesDraw
            delegate: Rectangle {
                width: modelData.w ;
                height: modelData.l
                x: modelData.c.x - 0.5 * width;
                y: modelData.c.y - 0.5*height
                color: "yellow"
            }
        }

        Slider {
            id: slider
            anchors.bottom: parent.bottom
            width: parent.width
            minimumValue: 1
            maximumValue: 100
            stepSize: 1
            value: 100
        }

        //handle selection point
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
            onClicked: {
                function appendList(obj, width, length, x, y)
                {
                    obj.push({ w: width, l: length, c: Qt.vector2d(x, y)})
                }

                switch(mouse.button)
                {
                    case Qt.LeftButton:
                    scene.targetPoint = Qt.vector2d(mouseX, mouseY)
                    nvigatableRobot.targetPosition = scene.targetPoint
                    break;

                    case Qt.RightButton:
                    appendList(scene.objects, 50, 50, mouseX - 25, mouseY - 25)
                    envi.objects = scene.objects
                    break;

                    case Qt.MiddleButton:
                        nvigatableRobot.center = Qt.vector2d(mouse.x, mouse.y)
                        break;

                }
            }

        }
    }
}

