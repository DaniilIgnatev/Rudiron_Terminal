import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0

Button{
    id: button_send
    property string color_default: "#cc5100"

    property string color_hovered: "#FF6600"

    property string color_pressed: "#993c00"

    text: "Отправить"
    font.letterSpacing: 0.5
    font.weight: Font.Light
    font.pointSize: Qt.platform.os === "windows" ? 7 : 9
    font.family: "Arial"
    Layout.rightMargin: 2
    Layout.fillHeight: true
    Layout.fillWidth: false
    Layout.preferredWidth: 80
    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    palette.buttonText: "white"

    background:
        MouseArea{
        id: mouse
        hoverEnabled: true

        property bool isPressed: false


        onPressed: {
            isPressed = true
            button_send.clicked()
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
