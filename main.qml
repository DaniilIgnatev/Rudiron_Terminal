import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

Window {
    visible: true
    title: qsTr("Rudiron Terminal")

    minimumWidth: 400
    minimumHeight: 200

    color: "#2f363d"

    ColumnLayout{
        anchors.fill: parent

        spacing: 3

        Transmitter{
            Layout.topMargin: 3
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.preferredHeight: 20
        }

        Receiver{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Options{
            Layout.bottomMargin: 3
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
