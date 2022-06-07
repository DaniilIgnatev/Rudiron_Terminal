import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

import com.VM 1.0

Window {
    visible: true
    title: "Рудирон Терминал"

    minimumWidth: 700
    minimumHeight: 350

    color: "#2f363d"

    TerminalVM{
        id: vm
    }

    ColumnLayout{
        anchors.fill: parent

        spacing: 4

        Transmitter{
            id: transmitter

            Layout.topMargin: 5
            Layout.leftMargin: 2
            Layout.rightMargin: 2

            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.minimumHeight: 30
            Layout.maximumHeight: 30
        }

        Log{
            id: log

            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Options{
            id: options

            Layout.bottomMargin: 4
            Layout.leftMargin: 4
            Layout.rightMargin: 2

            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.minimumHeight: 30
            Layout.maximumHeight: 30

            onFinishedInteraction: {
                transmitter.forceInputFocus()
            }
        }
    }

    Component.onCompleted: {
        transmitter.vm =vm.getTransmitterVM()
        log.vm = vm.getLogVM()
        options.vm = vm.getOptionsVM()
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}D{i:1}D{i:3}D{i:4}D{i:5}D{i:2}
}
##^##*/
