#include "logvm.hpp"

UART *LogVM::getUart() const
{
    return uart;
}

void LogVM::setUart(UART *newUart)
{
    uart = newUart;
}

LogVM::LogVM(QObject *parent)
    : QObject{parent}
{

}
