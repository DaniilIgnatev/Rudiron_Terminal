#include "uartpackage.h"

UARTPackage::UARTPackage(QObject *parent) : QObject(parent)
{

}

const QDateTime &UARTPackage::getDateTime() const
{
    return dateTime;
}

void UARTPackage::setDateTime(const QDateTime &newDateTime)
{
    if (dateTime == newDateTime)
        return;
    dateTime = newDateTime;
    emit dateTimeChanged();
}

const QByteArray &UARTPackage::getData() const
{
    return data;
}

void UARTPackage::setData(const QByteArray &newData)
{
    if (data == newData)
        return;
    data = newData;
    emit dataChanged();
}
