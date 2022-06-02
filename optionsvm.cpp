#include "optionsvm.hpp"

UART *OptionsVM::getUart() const
{
    return uart;
}

void OptionsVM::setUart(UART *newUart)
{
    uart = newUart;
}

OptionsVM::OptionsVM(QObject *parent)
    : QObject{parent}
{

}
