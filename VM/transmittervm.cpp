#include "transmittervm.hpp"

UART *TransmitterVM::getUart() const
{
    return uart;
}

void TransmitterVM::setUart(UART *newUart)
{
    uart = newUart;
}

TransmitterVM::TransmitterVM(QObject *parent)
    : QObject{parent}
{

}

void TransmitterVM::send(QString text)
{
    uart->writeRead(text.toUtf8(), 0);
}
