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

const QByteArray &UARTPackage::getData() const
{
    return _data;
}

void UARTPackage::setData(const QByteArray &newData)
{
    if (_data == newData)
        return;
    _data = newData;
    emit dataChanged();
}
