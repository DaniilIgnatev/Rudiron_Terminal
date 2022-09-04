#include "transmittervm.hpp"

TransmitterVM::TransmitterVM(QObject *parent)
    : IOptionsModelDelegateHolder{parent}
{
    connect(this, &TransmitterVM::optionsModelChanged, this, &TransmitterVM::onOptionsModelChanged);
}

UART *TransmitterVM::getUart() const
{
    return uart;
}

void TransmitterVM::setUart(UART *newUart)
{
    uart = newUart;
}

void TransmitterVM::send(QString text)
{
    if (uart->isOpen()){
        text.append(getOptionsModel()->getInputModel()->getStringEnd());
        QByteArray message = text.toUtf8();
        uart->writeRead(message, 0);
    }
    else{
        output("Выберите последовательный порт!\n");
    }
}

OptionsModel* TransmitterVM::getOptionsModel()
{
    return optionsModelDelegate->getOptionsModel();
}

void TransmitterVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    optionsModelDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *TransmitterVM::getOptionsModelDelegate() const
{
    return optionsModelDelegate;
}

void TransmitterVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    optionsModelDelegate = newDisplayModeDelegate;
    connect(optionsModelDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &TransmitterVM::optionsModelChanged);
}

void TransmitterVM::output(QString message)
{
    getOutputDelegate()->output(message);
}

void TransmitterVM::clear()
{
    getOutputDelegate()->clear();
}

IOutputDelegate *TransmitterVM::getOutputDelegate() const
{
    return outputDelegate;
}

void TransmitterVM::setOutputDelegate(IOutputDelegate *newOutputDelegate)
{
    outputDelegate = newOutputDelegate;
}

void TransmitterVM::onOptionsModelChanged()
{

}
