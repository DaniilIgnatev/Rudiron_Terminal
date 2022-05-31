import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout{

    ColumnLayout{
        Layout.fillHeight: true
        Layout.fillWidth: true

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: false
        }

        TextInput{
            selectByMouse: true
            cursorVisible: true
            Layout.fillHeight: true
            Layout.fillWidth: true

        }

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: false
        }
    }

    Button{
        Layout.fillHeight: true
        Layout.fillWidth: false

        Layout.preferredWidth: 70

        text: "Отправить"
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        flat: false
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:300}D{i:2}D{i:3}D{i:4}D{i:1}D{i:5}
}
##^##*/
