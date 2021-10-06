import QtQuick 2.2
import QtQuick.Layouts 1.2

Rectangle {
	id: root
	property bool togglable: false
	property bool toggled: false
	property alias text: textField.text
	color: toggled ? "lightblue" : "gray"

	MouseArea{
		anchors.fill: parent
		onClicked: root.toggled = !root.toggled
	}
	Text{
		id: textField
		anchors.fill: parent
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		
	}
}
