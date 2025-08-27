import QtQuick

// Item {
//     width: 400
//     height: 300

//     ListModel {
//         id: listmodel
//         ListElement { name: "xx"; age: 11 }
//         ListElement { name: "yy"; age: 12 }
//         ListElement { name: "zz"; age: 13 }
//     }

//     ListView {
//         id: listview
//         spacing: 5
//         anchors.fill: parent

//         //model: ["a", "b", "c"]
//         model: listmodel

//         delegate: Rectangle {
//             width: parent.width
//             height: 50
//             color: "gold"
//             border {
//                 color: "cyan"
//                 width: 1
//             }
//             Text {
//                 //id: name
//                 // text: modelData
//                 text: model.name
//                 anchors.centerIn: parent
//             }
//         }
//     }

// }
Item {
    Component {
            id: circleComponent

            Rectangle {
                width: 50
                height: 50
                radius: width / 2
                color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1)

                Behavior on x { NumberAnimation { duration: 500 } }
                Behavior on y { NumberAnimation { duration: 500 } }
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#f0f0f0"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // 动态创建圆形
                    var circle = circleComponent.createObject(parent, {
                        "x": mouseX - 25,
                        "y": mouseY - 25
                    });

                    // 5秒后自动删除
                    circle.destroy(5000);
                }
            }
        }
}
