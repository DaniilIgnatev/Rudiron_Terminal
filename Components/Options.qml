import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import com.VM 1.0
import "qrc:/Components/Rudiron"

Rectangle {
    id: root
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

        RudironSwitchBox{
            id: logSwitchBox
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignLeft

            default_value: "Вывод"
            model:
                ListModel {

                ListElement {
                    name: "Прокрутка:"
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
                    name: "Время:"
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
                    name: "Режим:"
                    values_available: [
                        ListElement{
                            value: "Строка"
                        },
                        ListElement{
                            value: "16-й"
                        },
                        ListElement{
                            value: "10-й"
                        },
                        ListElement{
                            value: "8-й"
                        },
                        ListElement{
                            value: "2-й"
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
                case 2:
                    optionsModel.outputMode = selected_value_index
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
            Layout.preferredWidth: 200
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

            onOpened: {
                model = vm.getAvailablePortNames()
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

        vm.openPortFailure.connect((portName) => {
                                       portName_comboBox.current_index = 0
                                   })

        logSwitchBox.model.get(0).values_index = vm.optionsModel.autoScroll ? 1 : 0
        logSwitchBox.model.get(1).values_index = vm.optionsModel.showTimeStamps ? 1 : 0
        logSwitchBox.model.get(2).values_index = vm.optionsModel.outputMode
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
