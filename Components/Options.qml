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

    signal finishedInteraction

    clip: true
    color: "#2f363d"

    RowLayout{
        id: layout
        anchors.fill: parent

        spacing: 15

        RudironOptionsBox{
            id: inputSwitchBox
            Layout.preferredWidth: 200
            Layout.alignment: Qt.AlignLeft

            default_value: "Передатчик"
            model:
                ListModel {

                ListElement {
                    name: "Порт:"
                    values_available: [
                        ListElement{
                            value: "отключен"
                        }
                    ]
                    values_index: 0
                }
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
                    values_index: 3
                }
                ListElement {
                    name: "Четность:"
                    values_available: [
                        ListElement{
                            value: "нет"
                        },
                        ListElement{
                            value: "чётный"
                        },
                        ListElement{
                            value: "нечетный"
                        },
                        ListElement{
                            value: "пробел"
                        },
                        ListElement{
                            value: "маркер"
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
                    name: "Управление:"
                    values_available: [
                        ListElement{
                            value: "нет"
                        },
                        ListElement{
                            value: "аппаратное"
                        },
                        ListElement{
                            value: "xon / xoff"
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Конец строки:"
                    values_available: [
                        ListElement{
                            value: "нет"
                        },
                        ListElement{
                            value: "\\n"
                        },
                        ListElement{
                            value: "\\r"
                        },
                        ListElement{
                            value: "\\r\\n"
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Режим:"
                    values_available: [
                        ListElement{
                            value: "строка"
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

            onOpened: {
                var portNames = vm.getAvailablePortNames()

                model.get(0).values_available.clear()

                var values_index = 0

                for(var i = 0; i < portNames.length; i++){
                    console.log(portNames[i])
                    model.get(0).values_available.append({
                                                             value: portNames[i]
                                                         })

                    if (vm.optionsModel.inputModel.portName === portNames[i]){
                        values_index = i
                    }
                }

                model.get(0).values_index = values_index
            }

            onModelChanged: {
                if (changed_indexes.length > 0){
                    var optionsModel = vm.optionsModel
                    var inputModel = optionsModel.inputModel

                    changed_indexes.forEach(model_index => {
                                                var delegate_model = model.get(model_index)
                                                var selected_value_index = delegate_model.values_index

                                                switch (model_index){
                                                    case 0:
                                                    inputModel.portName = delegate_model.values_available.get(selected_value_index).value
                                                    break
                                                    case 1:
                                                    inputModel.baudRate = delegate_model.values_available.get(selected_value_index).value
                                                    break
                                                    case 2:
                                                    inputModel.dataBits = Number(delegate_model.values_available.get(selected_value_index).value)
                                                    break
                                                    case 3:
                                                    if (selected_value_index === 0){
                                                        inputModel.parity = selected_value_index
                                                    }
                                                    else{
                                                        inputModel.parity = selected_value_index + 1
                                                    }
                                                    break
                                                    case 4:
                                                    switch(selected_value_index){
                                                        case 0:
                                                        inputModel.stopBits = 1
                                                        break
                                                        case 1:
                                                        inputModel.stopBits = 3
                                                        break
                                                        case 2:
                                                        inputModel.stopBits = 2
                                                        break
                                                    }
                                                    break
                                                    case 5:
                                                    inputModel.flowControl = selected_value_index
                                                    break
                                                    case 6:
                                                    switch(selected_value_index){
                                                        case 0:
                                                        inputModel.stringEnd = ""
                                                        break
                                                        case 1:
                                                        inputModel.stringEnd = "\n"
                                                        break
                                                        case 2:
                                                        inputModel.stringEnd = "\r"
                                                        break
                                                        case 3:
                                                        inputModel.stringEnd = "\r\n"
                                                        break
                                                    }
                                                    break
                                                    case 7:
                                                    inputModel.mode = selected_value_index
                                                    break
                                                }
                                            });

                    optionsModel.inputModel = inputModel
                    vm.onFinishedInputModelEditing()
                }

                finishedInteraction()
            }
        }

        RudironOptionsBox{
            id: outputSwitchBox
            Layout.preferredWidth: 100
            Layout.alignment: Qt.AlignLeft

            default_value: "Приемник"
            model:
                ListModel {

                ListElement {
                    name: "Прокрутка:"
                    values_available: [
                        ListElement{
                            value: "выкл."
                        },
                        ListElement{
                            value: "вкл."
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Время:"
                    values_available: [
                        ListElement{
                            value: "выкл."
                        },
                        ListElement{
                            value: "вкл."
                        }
                    ]
                    values_index: 0
                }
                ListElement {
                    name: "Режим:"
                    values_available: [
                        ListElement{
                            value: "строка"
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
                if (changed_indexes.length > 0){
                    var optionsModel = vm.optionsModel
                    var outputModel = optionsModel.outputModel

                    changed_indexes.forEach(model_index => {
                                                var delegate_model = model.get(model_index)
                                                var selected_value_index = delegate_model.values_index

                                                switch (model_index){
                                                    case 0:
                                                    outputModel.autoScroll = Boolean(selected_value_index)
                                                    break
                                                    case 1:
                                                    outputModel.showTimeStamps = Boolean(selected_value_index)
                                                    break
                                                    case 2:
                                                    outputModel.mode = selected_value_index
                                                    break
                                                }
                                            });

                    optionsModel.outputModel = outputModel
                    vm.onFinishedOutputModelEditing()
                }

                finishedInteraction()
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
        initializeFromOutputModel()
        initializeFromInputModel()
    }

    function initializeFromOutputModel(){
        outputSwitchBox.model.get(0).values_index = vm.optionsModel.outputModel.autoScroll ? 1 : 0
        outputSwitchBox.model.get(1).values_index = vm.optionsModel.outputModel.showTimeStamps ? 1 : 0
        outputSwitchBox.model.get(2).values_index = vm.optionsModel.outputModel.mode
    }

    function initializeFromInputModel(){
        var baudRate_index = 0
        for(var i = 0; i < inputSwitchBox.model.get(1).values_available.count; i++){
            if (inputSwitchBox.model.get(1).values_available.get(i).value === String(vm.optionsModel.inputModel.baudRate)){
                baudRate_index = i
                break
            }
        }
        inputSwitchBox.model.get(1).values_index = baudRate_index

        inputSwitchBox.model.get(2).values_index = vm.optionsModel.inputModel.dataBits - 5

        if (vm.optionsModel.inputModel.parity === 0){
            inputSwitchBox.model.get(3).values_index = vm.optionsModel.inputModel.parity
        }
        else{
            inputSwitchBox.model.get(3).values_index = vm.optionsModel.inputModel.parity - 1
        }

        switch(vm.optionsModel.inputModel.stopBits){
        case 1:
            inputSwitchBox.model.get(4).values_index = 0
            break
        case 3:
            inputSwitchBox.model.get(4).values_index = 1
            break
        case 2:
            inputSwitchBox.model.get(4).values_index = 2
            break
        }

        inputSwitchBox.model.get(5).values_index = vm.optionsModel.inputModel.flowControl

        switch(vm.optionsModel.inputModel.stringEnd){
        case "":
            inputSwitchBox.model.get(6).values_index = 0
            break
        case "\n":
            inputSwitchBox.model.get(6).values_index = 1
            break
        case "\r":
            inputSwitchBox.model.get(6).values_index = 2
            break
        case "\r\n":
            inputSwitchBox.model.get(6).values_index = 3
            break
        }

        inputSwitchBox.model.get(7).values_index = vm.optionsModel.inputModel.mode
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:30;width:640}
}
##^##*/
