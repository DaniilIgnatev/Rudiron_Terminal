import QtQuick 2.6
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

        Dispatcher{
            Layout.fillHeight: false
            Layout.fillWidth: true
            height: 20
        }

        Printer{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DispatcherOptions{
            Layout.fillHeight: false
            Layout.fillWidth: true
            height: 20
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}D{i:1}
}
##^##*/
