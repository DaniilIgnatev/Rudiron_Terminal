#include "transmittervm.hpp"

TransmitterVM::TransmitterVM(QObject *parent)
    : IDisplayMode{parent}
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

IDisplayMode::Enum TransmitterVM::getDisplayMode()
{
    return displayModeDelegate->getDisplayMode();
}

void TransmitterVM::setDisplayMode(IDisplayMode::Enum newDisplayMode)
{
    displayModeDelegate->setDisplayMode(newDisplayMode);
}

IDisplayMode *TransmitterVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void TransmitterVM::setDisplayModeDelegate(IDisplayMode *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IDisplayMode::displayModeChanged, this, &TransmitterVM::displayModeChanged);
}
