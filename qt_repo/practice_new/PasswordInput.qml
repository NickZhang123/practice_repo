import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 300
    height: 40
    radius: 5
    color: "gray"
    border.color: "#cce6ff"
    border.width: 1

    property alias text: passwordField.text
    property string placeholder: "input password here"
    property bool visiblePassword: false

    TextField {
        id: passwordField
        anchors {
            left: parent.left
            leftMargin: 8
            right: eyeButton.left
            rightMargin: 8
            verticalCenter: parent.verticalCenter
        }
        height: parent.height - 4

        font.pixelSize: 16
        font.family: "黑体"
        placeholderText: root.placeholder
        echoMode: root.visiblePassword ? TextInput.Normal : TextInput.Password

        background: Rectangle {
            color: "transparent"
        }
    }

    Image {
        id: eyeButton
        anchors {
            right: parent.right
            rightMargin: 8
            verticalCenter: parent.verticalCenter
        }
        width: 24
        height: 24
        source: root.visiblePassword
                ? "qrc:/icon/visibility_off.png"
                : "qrc:/icon/visibility_on.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: root.visiblePassword = !root.visiblePassword
        }
    }
}
