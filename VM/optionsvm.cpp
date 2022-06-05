#include "optionsvm.hpp"

OptionsVM::OptionsVM(QObject *parent): IOptionsModelDelegateHolder{parent}
{

}

UART *OptionsVM::getUart() const
{
    return uart;
}

void OptionsVM::setUart(UART *newUart)
{
    uart = newUart;
}

OptionsModel* OptionsVM::getOptionsModel()
{
    return displayModeDelegate->getOptionsModel();
}

void OptionsVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    displayModeDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *OptionsVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void OptionsVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &OptionsVM::optionsModelChanged);
}

void OptionsVM::output(QString message)
{
    getOutputDelegate()->output(message);
}

void OptionsVM::clear()
{
    getOutputDelegate()->clear();
}

IOutputDelegate *OptionsVM::getOutputDelegate() const
{
    return outputDelegate;
}

void OptionsVM::setOutputDelegate(IOutputDelegate *newOutputDelegate)
{
    outputDelegate = newOutputDelegate;
}

QStringList OptionsVM::availablePortNames()
{
    QStringList defaultValue("Отключен");
    QStringList available = uart->availablePortNames();
    defaultValue.append(available);
    return defaultValue;
}

void OptionsVM::onOptionsModelChanged(OptionsModel *newValue)
{
    QSerialPortInfo portInfo = QSerialPortInfo(newValue->getPortName());
    bool containsPort = !portInfo.isNull();

    if (containsPort){
        if (newValue->getPortName() != uart->getCurrentPortName()){
            if (uart->getCurrentPortName() != ""){
                uart->end();
                output("Закрыл порт " + uart->getCurrentPortName());
            }

            if (uart->begin(portInfo)){
                output("Открыл порт " + newValue->getPortName());
            }
            else{
                output("Ошибка открытия порта " + newValue->getPortName() + "!");
            }
        }
    }
    else{
        if (uart->getCurrentPortName() != ""){
            uart->end();
            output("Закрыл порт " + uart->getCurrentPortName());
        }
    }
}
