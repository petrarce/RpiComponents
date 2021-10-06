import QtQuick 2.2
import QtQuick.Layouts 1.2
import QtMultimedia 5.8
import Video 0.1


Rectangle {
	id:root
	property string deviceId: ""
	Layout.fillWidth: true
	Layout.fillHeight: true
	border.color: "green"
	color: "transparent"
	ColumnLayout {
		anchors.fill: parent
		VideoOutput {
			Layout.preferredHeight: 4/5 * root.height
			Layout.fillWidth: true
			source: mpSource
		}
		Rectangle {
			id: footer
			Layout.fillWidth: true
			Layout.fillHeight: true
			border.color: "red"
			border.width: 2
			color: "transparent"
			RowLayout{
				anchors.fill: parent
				Button {
					Layout.fillHeight: true
					Layout.fillWidth: true
					togglable: true
					text: "Record"
					
				}
			}
		}
	}

	resources: [
		MediaPlayer {
			id: mpSource
			source: "gst-pipeline: v4l2src device=" + deviceId + " ! decodebin ! videoconvert ! tee name=t ! queue ! qtvideosink t. ! queue leaky=1 ! x264enc ! mp4mux ! filesink location=/tmp/" + deviceId
			onSourceChanged: console.log(source)
			autoPlay: true
		}
	]
}
