import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

Window {
    visible: true
    title: qsTr("Hello World")

    minimumWidth: 400
    minimumHeight: 200

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Transmitter{
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.preferredHeight: 20
        }

        Receiver{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Options{
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.preferredHeight: 20
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}D{i:2}D{i:3}D{i:4}D{i:1}
}
##^##*/
