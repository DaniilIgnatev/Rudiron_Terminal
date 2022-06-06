#include "optionsvm.hpp"

OptionsVM::OptionsVM(QObject *parent): IOptionsModelDelegateHolder{parent}
{
    connect(this, &OptionsVM::optionsModelChanged, this, &OptionsVM::onOptionsModelChanged);
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
    return optionsModelDelegate->getOptionsModel();
}

void OptionsVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    optionsModelDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *OptionsVM::getOptionsModelDelegate() const
{
    return optionsModelDelegate;
}

void OptionsVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    optionsModelDelegate = newDisplayModeDelegate;
    connect(optionsModelDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &OptionsVM::optionsModelChanged);
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

QString OptionsVM::getDefaultPortName()
{
    return "Порт отключен";
}

QStringList OptionsVM::getAvailablePortNames()
{
    QStringList defaultValue("Порт отключен");
    QStringList available = uart->availablePortNames();
    defaultValue.append(available);
    return defaultValue;
}

void OptionsVM::onOptionsModelChanged(OptionsModel *newValue)
{
    QSerialPortInfo portInfo = QSerialPortInfo(newValue->getPortName());
    bool containsPort = !portInfo.isNull();

    if (containsPort){
        if (newValue->getPortName() != uart->getCurrentPortName() || !uart->isOpen()){
            if (uart->isOpen()){
                uart->end();
                output("Закрыл порт " + uart->getCurrentPortName());
            }

            if (uart->begin(portInfo)){
                output("Открыл порт " + newValue->getPortName());
            }
            else{
                output("Ошибка открытия порта " + newValue->getPortName() + "!");
                emit openPortFailure(newValue->getPortName());
            }
        }
    }
    else{
        if (uart->isOpen()){
            uart->end();
            output("Закрыл порт " + uart->getCurrentPortName());
        }
    }
}
