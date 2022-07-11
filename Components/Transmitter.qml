import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0
import "qrc:/Components/Rudiron"

RowLayout{
    property TransmitterVM vm

    spacing: 5

    signal forceInputFocus

    onForceInputFocus: {
        textInput.focus = true
    }

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
            font.family: "Arial"

            focus: true

            id: textInput

            color: "#d1d5da"
            selectionColor: "#0664d3"
            selectedTextColor: "#ffffff"

            font.pointSize: Qt.platform.os === "windows" ? 10 : 12
            font.letterSpacing: 0.5
            selectByMouse: true
            cursorVisible: true

            onAccepted: {
                vm.send(textInput.text)
                textInput.text = ""
            }

            TextInput {
                topPadding: 2
                leftPadding: 5
                anchors.fill: parent
                readOnly: true

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.family: "Arial"

                text: "Введите строку..."
                color: "#d1d5da"
                visible: !textInput.text

                font.pointSize: Qt.platform.os === "windows" ? 10 : 12
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
