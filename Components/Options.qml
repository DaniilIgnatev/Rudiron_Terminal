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
            Layout.alignment: Qt.AlignLeft

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

        RudironSwitchBox{
            id: logSwitchBox
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignLeft

            default_value: "Вывод"
            model:
                ListModel {

                ListElement {
                    name: "Автопрокрутка"
                    values_available: [
                        ListElement{
                            value: "Выкл."
                        },
                        ListElement{
                            value: "Вкл."
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Отметки времени"
                    values_available: [
                        ListElement{
                            value: "Выкл."
                        },
                        ListElement{
                            value: "Вкл."
                        }
                    ]
                    values_index: 0
                }
            }

            onModelChanged: {
                var optionsModel = vm.optionsModel
                var delegate_model = model.get(current_index)
                var selected_value_index = delegate_model.values_index

                switch (current_index){
                case 0:
                    optionsModel.autoScroll = Boolean(selected_value_index)
                    break
                case 1:
                    optionsModel.showTimeStamps = Boolean(selected_value_index)
                    break
                }

                vm.optionsModel = optionsModel
            }
        }

//        RudironSwitchBox{
//            Layout.preferredWidth: 150
//            Layout.alignment: Qt.AlignLeft

//            model: [
//                "Бит в секунду",
//                "Биты данных",
//                "Четность",
//                "Стоповые биты",
//                "Конец строки"
//            ]
//        }

        RudironComboBox{
            id: portName_comboBox
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignLeft

            default_value: "Порт отключен"
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
        }

        RudironButton{
            Layout.alignment: Qt.AlignRight
            text: "Очистить"

            onClicked: {
                vm.clear()
            }
        }
    }

    onVmChanged: {
        vm.optionsModelChanged.connect((model) => {
                                           console.log("Options model changed:\n" + model.printable())
                                       })


        displayMode_comboBox.current_index = vm.optionsModel.displayMode
        logSwitchBox.model.get(0).values_index = vm.optionsModel.autoScroll ? 1 : 0
        logSwitchBox.model.get(1).values_index = vm.optionsModel.showTimeStamps ? 1 : 0
        portName_comboBox.model = vm.getAvailablePortNames()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
