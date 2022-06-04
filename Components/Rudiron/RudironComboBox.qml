import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0

MouseArea{
    id: root_mouse

    property var model
    property alias current_index: combobox.currentIndex
    property var current_value

    Layout.fillHeight: true
    Layout.margins: -5
    Layout.preferredWidth: 100

    hoverEnabled: true

    onHoveredChanged: {
        displayMode_canvas.requestPaint();
    }

    ComboBox{
        id: combobox
        anchors.fill: parent

        model: root_mouse.model

        onCurrentIndexChanged: {
            if (currentIndex >= 0){
                root_mouse.current_value = root_mouse.model[currentIndex]
            }
        }

        font.letterSpacing: currentIndex == 0 ? 0.5 : 1.5

        background: Rectangle {
            color: "#1d2125"
            border.color: parent.pressed ? "#262626" : "#1d2125"
            border.width: parent.visualFocus ? 2 : 1
        }

        contentItem:
            Text {
            padding: 0

            text: parent.displayText
            font: parent.font

            color: parent.pressed ? "#d1d5da" : (root_mouse.containsMouse ? "white" : "#d1d5da")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideMiddle
        }

        indicator:
            Canvas {
            property int rotation_angle: 0

            id: displayMode_canvas
            x: combobox.width - width - combobox.rightPadding
            y: combobox.topPadding + (combobox.availableHeight - height) / 2
            width: 12
            height: 8
            contextType: "2d"
            transform: Rotation {
                axis.x: 0.5;
                axis.y: 0.0;
                axis.z: 0.0;
                origin.x: displayMode_canvas.width / 2;
                origin.y: displayMode_canvas.height / 2;
                angle: displayMode_canvas.rotation_angle;
            }
            state: combobox.popup.visible ? "rotated" : "default"

            states: [
                State {
                    name: "default"
                    PropertyChanges { target: displayMode_canvas; rotation_angle: 0}
                },
                State {
                    name: "rotated"
                    PropertyChanges { target: displayMode_canvas; rotation_angle: 180}
                }
            ]

            transitions: Transition {
                PropertyAnimation { properties: "rotation_angle"; easing.type: Easing.InOutQuad }
            }

            property string color_default: "#cc5100"
            property string color_hovered: "#FF6600"
            property string color_pressed: "#993c00"

            Connections {
                target: combobox
                function onPressedChanged() { displayMode_canvas.requestPaint(); }
            }

            onPaint: {
                context.reset();
                context.moveTo(0, 0);
                context.lineTo(width, 0);
                context.lineTo(width / 2, height);
                context.closePath();

                if (parent.pressed){
                    context.fillStyle = color_pressed
                }
                else{
                    context.fillStyle = root_mouse.containsMouse ? color_hovered : color_default
                }
                context.fill();
            }
        }
        popup:
            Popup {
            y: combobox.height - 1
            width: combobox.width
            implicitHeight: contentItem.implicitHeight
            padding: 1
            leftMargin: 0

            contentItem: ListView {
                interactive: false
                clip: true
                implicitHeight: contentHeight
                model: combobox.popup.visible ? combobox.delegateModel : null
                currentIndex: combobox.highlightedIndex

                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle{
                border.width: 1
                border.color: "#2f363d"
            }
        }

        delegate:
            MouseArea{
            id: delegate_mouse
            property int indexOfThisDelegate: index

            width: combobox.width
            height: 30
            hoverEnabled: true

            onClicked:{
                combobox.currentIndex = index
                combobox.popup.close()
            }

            Rectangle
            {
                anchors.fill: parent
                clip: true

                color: delegate_mouse.containsMouse ? "#4c5763" : "#2f363d"

                Text {
                    anchors.fill: parent
                    padding: 0

                    text: combobox.model[index]
                    font: combobox.font

                    color: delegate_mouse.pressed ? "#d1d5da" : (delegate_mouse.containsMouse ? "white" : "#d1d5da")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideMiddle
                }
            }
        }
    }
}
