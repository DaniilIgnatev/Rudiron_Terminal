#include "logvm.hpp"

LogVM::LogVM(QObject *parent)
    : QObject{parent}
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

DisplayMode::Enum LogVM::getDisplayMode() const
{
    return displayMode;
}

void LogVM::setDisplayMode(DisplayMode::Enum newDisplayMode)
{
    if (displayMode == newDisplayMode)
        return;
    displayMode = newDisplayMode;
    emit displayModeChanged();
}

const QByteArray &UARTPackage::getData() const
{
    return data;
}

const QDateTime &UARTPackage::getDateTime() const
{
    return dateTime;
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
    switch (displayMode) {
        case DisplayMode::Enum::TEXT:
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
