#include "optionsvm.hpp"

UART *OptionsVM::getUart() const
{
    return uart;
}

void OptionsVM::setUart(UART *newUart)
{
    uart = newUart;
}

void OptionsVM::setDisplayMode(DisplayMode::Enum mode)
{

}

DisplayMode::Enum OptionsVM::getDisplayMode()
{

}

OptionsVM::OptionsVM(QObject *parent)
    : QObject{parent}
{

}
