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
    LogVM_Package* package = new LogVM_Package();
    package->data = uart->getRXBuffer();
    package->dateTime = QDateTime::currentDateTime();
    uart->clearRXBuffer();
    receivedPackages.append(package);

    QString appendedLog = convertToLog(package);
    emit logAppended(appendedLog);
}

LogVM::DisplayModeEnum LogVM::getDisplayMode() const
{
    return displayMode;
}

void LogVM::setDisplayMode(DisplayModeEnum newDisplayMode)
{
    if (displayMode == newDisplayMode)
        return;
    displayMode = newDisplayMode;
    emit displayModeChanged();
}

const QByteArray &LogVM_Package::getData() const
{
    return data;
}

const QDateTime &LogVM_Package::getDateTime() const
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

QString LogVM::convertToLog(const LogVM_Package* package)
{
    switch (displayMode) {
        case DisplayModeEnum::TEXT:
        return convertPackageAsText(package);
    default:
        return convertPackageAsText(package);
    }
}

QString LogVM::convertPackageAsText(const LogVM_Package* package)
{
    QString text;
    text.append(QString::number(package->dateTime.time().hour()));
    text.append(":");
    text.append(QString::number(package->dateTime.time().minute()));
    text.append(":");
    text.append(QString::number(package->dateTime.time().second()));
    text.append(":");
    text.append(QString::number(package->dateTime.time().msec()));
    text.append(" -> ");
    text.append(package->data);
    return text;
}
