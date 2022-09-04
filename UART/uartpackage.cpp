#include "uartpackage.hpp"

UARTPackage::UARTPackage(QObject *parent) : QObject(parent)
{
    
}

const QDateTime &UARTPackage::getDateTime() const
{
    return _dateTime;
}

void UARTPackage::setDateTime(const QDateTime &newDateTime)
{
    if (_dateTime == newDateTime)
        return;
    _dateTime = newDateTime;
    emit dateTimeChanged();
}

const QByteArray UARTPackage::getData() const
{
    return _data;
}

void UARTPackage::setData(const QByteArray newData)
{
    if (_data == newData)
        return;
    _data = newData;
    emit dataChanged();
}

QString UARTPackage::getPortName() const
{
    return _portName;
}

void UARTPackage::setPortName(const QString &value)
{
    _portName = value;
    emit portNameChanged();
}

bool UARTPackage::isValid()
{
    return _data.endsWith('\n');
}

bool UARTPackage::getIsLogOutput() const
{
    return _isLogOutput;
}

void UARTPackage::setIsLogOutput(bool value)
{
    if (_isLogOutput == value)
        return;
    _isLogOutput = value;
    emit logOutputChanged();
}
