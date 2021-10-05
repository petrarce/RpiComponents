import QtQuick 2.2
import QtQuick.Layouts 1.12
import QtMultimedia 5.15
import Video 0.1


Rectangle {
    id:root
    property string deviceId: ""
    Layout.fillWidth: true
    Layout.fillHeight: true
    border.color: "green"
    color: "transparent"
    resources: MediaPlayer {
        id: mpSource
        source: "gst-pipeline: v4l2src device=" + deviceId + " ! decodebin ! videoconvert ! qtvideosink"
        autoPlay: true
    }
    VideoOutput {
        anchors.fill: parent
        source: mpSource
    }
}
