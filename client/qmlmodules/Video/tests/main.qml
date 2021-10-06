import QtQuick 2.2
import QtQuick.Layouts 1.2
import QtMultimedia 5.8
import Video 0.1

Rectangle {
    width: 1000
    height: 500
    property var deviceIds: QtMultimedia.availableCameras
    onDeviceIdsChanged: console.log("deviceIds: ", JSON.stringify(deviceIds))
    property var deviceFiles: VideoDevicesPoll.listDevices
    onDeviceFilesChanged: console.log("deviceFiles:", JSON.stringify(deviceFiles))

    GridLayout{
        anchors.fill: parent
        columns: 3
        Repeater {
            model: deviceFiles
            delegate: CameraView {
                deviceId: modelData
            }
        }
    }



}
