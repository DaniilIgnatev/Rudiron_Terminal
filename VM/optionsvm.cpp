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

QStringList OptionsVM::availablePortNames()
{
    return uart->availablePortNames();
}

void OptionsVM::onOptionsModelChanged(OptionsModel *newValue)
{
    if (newValue->getPortName() == uart->getCurrentPortName()){
        qDebug() << "Порт " << newValue->getPortName() << " уже открыт!";
    }
    else{
        QSerialPortInfo portInfo = QSerialPortInfo(newValue->getPortName());
        if (uart->begin(portInfo)){
            qDebug() << "Открыл порт " << newValue->getPortName();
        }
        else{
            qDebug() << "Ошибка открытия порта " << newValue->getPortName() << "!";
        }
    }
}
