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
            id: displayMode_comboBox

            model: [
                "Строка",
                "16-й",
                "10-й",
                "8-й",
                "2-й",
            ]

            onCurrent_indexChanged: {
                if (vm){
                    var current_model = vm.optionsModel
                    current_model.displayMode = current_index
                    vm.optionsModel = current_model
                }
            }
        }

        RudironComboBox{
            Layout.preferredWidth: 150

            model: ListModel {
                ListElement { key: "Автопрокрутка"; value: OptionsModel.TEXT }
                ListElement { key: "Отметки времени"; value: OptionsModel.HEX }
            }

            onCurrent_valueChanged: {

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

            }
        }

        RudironComboBox{
            id: portName_comboBox

            model: []

            onCurrent_valueChanged: {
                if (vm){
                    var model = vm.optionsModel
                    model.portName = current_value
                    vm.optionsModel = model
                }
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

    onVmChanged: {
        vm.onOptionsModelChanged.connect((model) => {
                                             console.log("Options model changed:\n" + model.printable())
                                         })

        portName_comboBox.model = vm.availablePortNames()
        displayMode_comboBox.current_index = vm.optionsModel.displayMode
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
