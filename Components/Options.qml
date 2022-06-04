import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0
import "qrc:/Components/Rudiron"

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

        spacing: 15

        RudironComboBox{
            model: ListModel {
                ListElement { key: "Строка"; value: OptionsModel.TEXT }
                ListElement { key: "16-й"; value: OptionsModel.HEX }
                ListElement { key: "10-й"; value: OptionsModel.DEC }
                ListElement { key: "8-й"; value: OptionsModel.OCT }
                ListElement { key: "2-й"; value: OptionsModel.BIN }
            }

            onCurrent_valueChanged: {
                var current_model = vm.optionsModel
                current_model.displayMode = current_value
                vm.optionsModel = current_model
            }
        }

        RudironComboBox{
            Layout.preferredWidth: 150

            model: ListModel {
                ListElement { key: "Автопрокрутка"; value: OptionsModel.TEXT }
                ListElement { key: "Отметки времени"; value: OptionsModel.HEX }
            }

            onCurrent_valueChanged: {
                var current_model = vm.optionsModel
                current_model.displayMode = current_value
                vm.optionsModel = current_model
            }
        }

        RudironComboBox{
            Layout.preferredWidth: 150

            model: ListModel {
                ListElement { key: "Бит в секунду"; value: OptionsModel.TEXT }
                ListElement { key: "Биты данных"; value: OptionsModel.HEX }
                ListElement { key: "Четность"; value: OptionsModel.DEC }
                ListElement { key: "Стоповые биты"; value: OptionsModel.OCT }
                ListElement { key: "Конец строки"; value: OptionsModel.OCT }
            }

            onCurrent_valueChanged: {
                var current_model = vm.optionsModel
                current_model.displayMode = current_value
                vm.optionsModel = current_model
            }
        }

        RudironComboBox{
            model: ListModel {
                ListElement { key: "COM1"; value: OptionsModel.TEXT }
                ListElement { key: "COM2"; value: OptionsModel.HEX }
            }

            onCurrent_valueChanged: {
                var current_model = vm.optionsModel
                current_model.displayMode = current_value
                vm.optionsModel = current_model
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RudironButton{
            text: "Очистить"
        }
    }

    Component.onCompleted: {
        vm.onOptionsModelChanged.connect((model) => {
                                             console.log("Options model changed:\n" + model.printable())
                                         })

        var current_model = vm.optionsModel
        current_model.displayMode = OptionsModel.TEXT
        vm.optionsModel = current_model
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
