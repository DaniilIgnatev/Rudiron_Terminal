import QtQuick 2.15
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0

RowLayout{
    property TransmitterVM vm

    spacing: 2

    Rectangle {
        Layout.leftMargin: 2
        Layout.rightMargin: 2

        Layout.fillHeight: true
        Layout.fillWidth: true

        clip: true
        color: "#1d2125"

        TextInput{
            topPadding: 2
            leftPadding: 2
            anchors.fill: parent

            id: textInput

            text: "Рудирон!"
            color: "#d1d5da"
            selectionColor: "#0664d3"
            selectedTextColor: "#ffffff"

            font.pointSize: 9
            selectByMouse: true
            cursorVisible: true
        }
    }

    Button{
        id: button_send
        property string color_default: "#cc5100"

        property string color_hovered: "#FF6600"

        property string color_pressed: "#993c00"

        text: "Отправить"
        font.letterSpacing: 0.15
        font.weight: Font.Light
        font.pointSize: 7
        font.family: "Verdana"
        Layout.rightMargin: 2
        Layout.fillHeight: true
        Layout.fillWidth: false
        Layout.preferredWidth: 70
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        palette.buttonText: "white"

        background:
            MouseArea{
            id: mouse
            hoverEnabled: true

            property bool isPressed: false


            onPressed: {
                isPressed = true
                vm.send(textInput.text)
            }
            onReleased: {
                isPressed = false
            }

            Rectangle{
                anchors.fill: parent

                color: {
                    if (mouse.isPressed){
                        return button_send.color_pressed
                    }
                    else{
                        return mouse.containsMouse ? button_send.color_hovered : button_send.color_default
                    }
                }

                border.color: "#26282a"
                border.width: 1
                radius: 4
            }
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:300}D{i:2}D{i:1}D{i:3}
}
##^##*/
