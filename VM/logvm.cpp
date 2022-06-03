#include "logvm.hpp"

LogVM::LogVM(QObject *parent)
    : IDisplayMode{parent}
{

}

UART *LogVM::getUart() const
{
    return uart;
}

void LogVM::setUart(UART *newUart)
{
    uart = newUart;
    connect(uart, &UART::available, this, &LogVM::uartAvailable);
}

IDisplayMode::Enum LogVM::getDisplayMode()
{
    return displayModeDelegate->getDisplayMode();
}

void LogVM::setDisplayMode(IDisplayMode::Enum newDisplayMode)
{
    displayModeDelegate->setDisplayMode(newDisplayMode);
}

IDisplayMode *LogVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void LogVM::setDisplayModeDelegate(IDisplayMode *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IDisplayMode::displayModeChanged, this, &LogVM::displayModeChanged);
}

void LogVM::uartAvailable()
{
    UARTPackage* package = new UARTPackage();
    package->setData(uart->getRXBuffer());
    package->setDateTime(QDateTime::currentDateTime());
    uart->clearRXBuffer();
    receivedPackages.append(package);

    QString appendedLog = convertToLog(package);
    emit logAppended(appendedLog);
}

QString LogVM::getLog()
{
    QString log;
    for(int i = 0; i < receivedPackages.count(); i++){
        auto package = receivedPackages.at(i);
        log += convertToLog(package);
    }

    return log;
}

QString LogVM::convertToLog(const UARTPackage* package)
{
    switch (getDisplayMode()) {
        case IDisplayMode::Enum::TEXT:
        return convertPackageAsText(package);
    default:
        return convertPackageAsText(package);
    }
}

QString LogVM::convertPackageAsText(const UARTPackage* package)
{
    QString text;
    text.append(QString::number(package->getDateTime().time().hour()));
    text.append(":");
    text.append(QString::number(package->getDateTime().time().minute()));
    text.append(":");
    text.append(QString::number(package->getDateTime().time().second()));
    text.append(":");
    text.append(QString::number(package->getDateTime().time().msec()));
    text.append(" -> ");
    text.append(package->getData());
    return text;
}
