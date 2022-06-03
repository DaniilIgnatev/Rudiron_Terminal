import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0

Rectangle {
    property OptionsVM vm

    Layout.leftMargin: 2
    Layout.rightMargin: 2

    Layout.fillHeight: true
    Layout.fillWidth: true

    clip: true
    color: "#2f363d"

    RowLayout{
        id: layout
        anchors.fill: parent

        spacing: 0

        R_ComboBox{
            model: ListModel {
                ListElement { key: "Строка"; value: LogVM.TEXT }
                ListElement { key: "16-й"; value: LogVM.HEX }
                ListElement { key: "8-й"; value: LogVM.OCT }
                ListElement { key: "2-й"; value: LogVM.BIN }
            }

            onCurrent_valueChanged: {
                vm.displayMode = current_value
            }
        }

        CheckBox {
            id: checkBox
            text: "Автопрокрутка"
            tristate: false
            checkState: Qt.Checked
            Layout.fillWidth: false
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: {
        vm.displayMode = IDisplayMode.TEXT
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
