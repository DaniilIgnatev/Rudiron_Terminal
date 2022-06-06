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
            id: outputSwitchBox
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
                            value: "2-й"
                        },
                        ListElement{
                            value: "8-й"
                        },
                        ListElement{
                            value: "10-й"
                        },
                        ListElement{
                            value: "16-й"
                        }
                    ]
                    values_index: 0
                }
            }

            onModelChanged: {
                var optionsModel = vm.optionsModel

                changed_indexes.forEach(model_index => {
                                                  var delegate_model = model.get(model_index)
                                                  var selected_value_index = delegate_model.values_index

                                                  switch (model_index){
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
                                              });

                vm.optionsModel = optionsModel
            }
        }

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

        RudironSwitchBox{
            id: inputSwitchBox
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignLeft

            default_value: "Ввод"
            model:
                ListModel {

                ListElement {
                    name: "Бит в секунду:"
                    values_available: [
                        ListElement{
                            value: "300"
                        },
                        ListElement{
                            value: "1200"
                        },
                        ListElement{
                            value: "2400"
                        },
                        ListElement{
                            value: "4800"
                        },
                        ListElement{
                            value: "9600"
                        },
                        ListElement{
                            value: "19200"
                        },
                        ListElement{
                            value: "38400"
                        },
                        ListElement{
                            value: "57600"
                        },
                        ListElement{
                            value: "115200"
                        },
                        ListElement{
                            value: "230400"
                        },
                        ListElement{
                            value: "250000"
                        },
                        ListElement{
                            value: "500000"
                        }
                    ]
                    values_index: 8
                }
                ListElement {
                    name: "Биты данных:"
                    values_available: [
                        ListElement{
                            value: "4"
                        },
                        ListElement{
                            value: "5"
                        },
                        ListElement{
                            value: "6"
                        },
                        ListElement{
                            value: "7"
                        },
                        ListElement{
                            value: "8"
                        }
                    ]
                    values_index: 4
                }
                ListElement {
                    name: "Четность:"
                    values_available: [
                        ListElement{
                            value: "Нет"
                        },
                        ListElement{
                            value: "Чет"
                        },
                        ListElement{
                            value: "Нечет"
                        },
                        ListElement{
                            value: "Маркер"
                        },
                        ListElement{
                            value: "Пробел"
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Стоповые биты:"
                    values_available: [
                        ListElement{
                            value: "1"
                        },
                        ListElement{
                            value: "1.5"
                        },
                        ListElement{
                            value: "2"
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Конец строки:"
                    values_available: [
                        ListElement{
                            value: "Нет"
                        },
                        ListElement{
                            value: "NL"
                        },
                        ListElement{
                            value: "CR"
                        },
                        ListElement{
                            value: "NL & CR"
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
                            value: "2-й"
                        },
                        ListElement{
                            value: "8-й"
                        },
                        ListElement{
                            value: "10-й"
                        },
                        ListElement{
                            value: "16-й"
                        }
                    ]
                    values_index: 0
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

        vm.openPortFailure.connect((portName) => {
                                       portName_comboBox.current_index = 0
                                   })

        outputSwitchBox.model.get(0).values_index = vm.optionsModel.autoScroll ? 1 : 0
        outputSwitchBox.model.get(1).values_index = vm.optionsModel.showTimeStamps ? 1 : 0
        outputSwitchBox.model.get(2).values_index = vm.optionsModel.outputMode
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
