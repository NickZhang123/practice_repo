import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("qml test")
    Test1 {
        id: test1
        width: parent.width
        height: parent.height
    }

    // Image {
    //     id: idx
    //     x:200
    //     width: 200
    //     height: 200
    //     source: "qrc:/icon/visibility_on.png"
    // }
}
