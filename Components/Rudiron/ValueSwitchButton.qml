import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Canvas{
    id: root

    Layout.preferredWidth: 12
    Layout.preferredHeight: 8

    contextType: "2d"

    property string color_default: "#cc5100"
    property string color_hovered: "#FF6600"
    property string color_pressed: "#993c00"

    signal clicked()

    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            root.clicked()
        }

        onPressed: {
            root.requestPaint()
        }
        onReleased: {
            root.requestPaint()
        }
        onContainsMouseChanged: {
            root.requestPaint()
        }
    }

    onPaint: {
        context.reset();
        context.moveTo(0, 0);
        context.lineTo(width, 0);
        context.lineTo(width / 2, height);
        context.closePath();

        if (mouse.pressed){
            context.fillStyle = color_pressed
        }
        else{
            context.fillStyle = mouse.containsMouse ? color_hovered : color_default
        }
        context.fill();
    }
}
