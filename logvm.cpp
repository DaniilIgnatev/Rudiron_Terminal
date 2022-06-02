#include "logvm.hpp"

UART *LogVM::getUart() const
{
    return uart;
}

void LogVM::setUart(UART *newUart)
{
    uart = newUart;
    connect(uart, &UART::available, this, &LogVM::uartAvailable);
}

void LogVM::uartAvailable()
{
    LogVM_Package* p = new LogVM_Package();
    p->data = uart->getRXBuffer();
    p->dateTime = QDateTime::currentDateTime();
    uart->clearRXBuffer();
    receivedPackages.append(p);
    emit newPackageReceived(p);
}

QString LogVM::getLog(LogVM::DisplayModeEnum mode)
{
    switch (mode) {
        case DisplayModeEnum::TEXT:
        return getLogAsText();
    default:
        return getLogAsText();
    }
}

QString LogVM::getLogAsText()
{
    return "Доделать!!!";
}

LogVM::LogVM(QObject *parent)
    : QObject{parent}
{

}

const QByteArray &LogVM_Package::getData() const
{
    return data;
}

const QDateTime &LogVM_Package::getDateTime() const
{
    return dateTime;
}
