import QtQuick
import QtQuick.Controls

// Column {
//     Button {
//         width: 40
//         height: 30
//         text: "tt"
//     }

//     Rectangle {
//         width: 200
//         height: 100
//         color: "gold"
//     }
//     Rectangle {
//         width: 200
//         height: 100
//         color: "darkseagreen"
//     }
//     Rectangle {
//         width: 200
//         height: 100
//         color: "mediumpurple"
//     }
// }

// Column {
//     id: column
//     Rectangle {
//         width: 100
//         height: 100
//         color: "red"
//     }
//     Rectangle {
//         width: 100
//         height: 100
//         color: "blue"
//     }
//     Rectangle {
//         width: 100
//         height: 100
//         color: "green"
//     }

//     Button {
//         text: "删除第2项"
//         onClicked: {
//             column.children[1].destroy();  // 删除第二个子项
//         }
//     }
// }

// Column {
//     Repeater {
//         id: rep
//         model: ListModel {
//             ListElement { name: "Item 1"; color: "gold" }
//             ListElement { name: "Item 2"; color: "mediumPurple" }
//             ListElement { name: "Item 3"; color: "pink" }
//             ListElement { name: "Item 4"; color: "cyan" }
//         }

//         delegate: Rectangle {
//             // id: model.name           // 错误，id是个静态值
//             property string itemId: "rect_" + index  // 为每个矩形设置唯一ID（使用索引）
//             width: 100
//             height: 50
//             //color: modelData.color    // 直接访问 modelData.color
//             color: model.color          // 使用 modelData.color 来绑定颜色
//             border.color: "red"

//             Text {
//                 text: model.name        // 显示项目名称
//                 anchors.centerIn: parent
//                 font.bold: true
//                 color: "black"
//             }
//         }
//     }

//     Button {
//         text: "删除第2项"
//         onClicked: {
//             rep.model.remove(1);  // 删除第二项
//         }
//         // 添加一些样式
//         background: Rectangle {
//             color: parent.down ? "#cccccc" : "#ffffff"
//             border.color: "#aaaaaa"
//             radius: 4
//         }
//     }
// }

Row {
    Repeater {
        id: rep
        model: ListModel {
            ListElement { name: "Item 1"; color: "gold" }
            ListElement { name: "Item 2"; color: "mediumPurple" }
            ListElement { name: "Item 3"; color: "pink" }
            ListElement { name: "Item 4"; color: "cyan" }
        }
        delegate: Button {
            text: model.name
            onClicked: {
                console.log(model.color)
            }
            background: Rectangle {
                color: model.color
                radius: 2
            }
        }
    }
}
