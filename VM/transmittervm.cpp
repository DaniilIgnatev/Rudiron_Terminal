#include "transmittervm.hpp"

TransmitterVM::TransmitterVM(QObject *parent)
    : IOptionsModelDelegate{parent}
{

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
    uart->writeRead(text.toUtf8(), 0);
}

OptionsModel* TransmitterVM::getOptionsModel()
{
    return displayModeDelegate->getOptionsModel();
}

void TransmitterVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    displayModeDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *TransmitterVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void TransmitterVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &TransmitterVM::optionsModelChanged);
}
