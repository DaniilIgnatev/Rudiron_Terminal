import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0
import "qrc:/Components/Rudiron"

RowLayout{
    property TransmitterVM vm

    spacing: 5

    Rectangle {
        Layout.leftMargin: 2
        Layout.rightMargin: 2

        Layout.fillHeight: true
        Layout.fillWidth: true

        clip: true
        color: "#1d2125"

        TextInput{
            topPadding: 2
            leftPadding: 5
            anchors.fill: parent

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            focus: true

            id: textInput

            color: "#d1d5da"
            selectionColor: "#0664d3"
            selectedTextColor: "#ffffff"

            font.pointSize: 12
            font.letterSpacing: 0.5
            selectByMouse: true
            cursorVisible: true

            onAccepted: {
                sendText()
            }

            TextInput {
                topPadding: 2
                leftPadding: 5
                anchors.fill: parent
                readOnly: true

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                text: "Введите строку..."
                color: "#d1d5da"
                visible: !textInput.text

                font.pointSize: 12
                font.letterSpacing: 0.5
                selectByMouse: false
                cursorVisible: false
            }
        }
    }

    RudironButton{
        onClicked: {
            if (textInput.text != ""){
                vm.send(textInput.text)
                textInput.text = ""
            }
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:300}
}
##^##*/
