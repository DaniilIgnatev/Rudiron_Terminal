#include "uart.hpp"
#include <QThread>
#include <QMetaEnum>

#include <QCoreApplication>


UART::UART(QObject *parent)
    : QObject{parent}
{

}

int UART::getByte(int at)
{
    if (at >= this->rx_buffer_index){
        return -1;
    }
    else{
        return this->rx_buffer[at];
    }
}

bool UART::begin(QSerialPortInfo port)
{
    serial = new QSerialPort(port, this);

    //    connect(serial, &QSerialPort::errorOccurred, this, &UART::errorSlot);
    connect(serial, &QSerialPort::readyRead, this, &UART::readyReadSlot);

    if (!serial->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections)){
        return false;
    }
    if (!serial->setDataBits(QSerialPort::Data8)){
        return false;
    }
    if (!serial->setStopBits(QSerialPort::OneStop)){
        return false;
    }
    if (!serial->setParity(QSerialPort::NoParity)){
        return false;
    }
    if (!serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl)){
        return false;
    }

    if (!serial->open(QIODevice::ReadWrite)) {
        return false;
    }

    while(!serial->isOpen()){
        QThread::currentThread()->msleep(5);
    }

    return true;
}

void UART::end()
{
    serial->close();
    serial->deleteLater();
}

void UART::setBaudRate(qint32 rate)
{
    serial->setBaudRate(rate);
}

int UART::getEventLoopDelay()
{
    return 8000 / serial->baudRate() / 14400;
}

void UART::errorSlot(QSerialPort::SerialPortError error){
    if (error != QSerialPort::NoError && error != QSerialPort::TimeoutError){
        QMetaEnum metaEnum = QMetaEnum::fromType<QSerialPort::SerialPortError>();
        QString error_str = metaEnum.valueToKey(error);
        qDebug() << "Serial error: " << error_str;
        qDebug() << serial->errorString();
    }
}

#ifdef _WIN32
void UART::writeSync()
{
    for (int i = 0; i < 15; i++){
        serial->write(QByteArray(1, 0));
    }

    serial->waitForBytesWritten();
}

void UART::writeRead(QByteArray buffer, int waitRXBytes)
{
    serial->write(buffer);
    serial->waitForBytesWritten();
    serial->waitForReadyRead(1);

    if (waitRXBytes){
        while (rx_buffer_index < waitRXBytes){
            serial->waitForReadyRead(0);
        }
        while (rx_buffer_index > waitRXBytes) {
            popByte();
        }
    }
}

#else
void UART::writeSync()
{
    serial->write(QByteArray(1, 0));
    serial->waitForReadyRead(1);
}

void UART::writeRead(QByteArray buffer, int waitRXBytes)
{
    if (waitRXBytes > 0){
        serial->write(buffer);
        serial->waitForReadyRead(read_delay);

        while (rx_buffer_index < waitRXBytes){
            QThread::currentThread()->usleep(getEventLoopDelay());
            serial->waitForReadyRead(read_delay);
        }
    }
    else{
        serial->write(buffer);
        serial->waitForReadyRead(10);
    }
}
#endif

int UART::readByte()
{
    if (serial->atEnd()){
        return -1;
    }
    else{
        if (this->rx_buffer_index < this->rx_buffer_size){
            char byte = serial->read(1).at(0);
            this->rx_buffer[this->rx_buffer_index] = byte;
            this->rx_buffer_index++;
            return byte;
        }
        else{
            return -1;
        }
    }
}

void UART::readyReadSlot()
{
    while (!serial->atEnd()) {
        readByte();
    }
}

int UART::popByte()
{
    if (rx_buffer_index == 0){
        return -1;
    }

    char byte = rx_buffer[0];

    for (int i = 1; i < rx_buffer_size; i++){
        rx_buffer[i - 1] = rx_buffer[i];
    }

    rx_buffer[rx_buffer_size - 1] = 0;
    rx_buffer_index -= 1;

    return byte;
}

void UART::waitRead(int timeout)
{
    int time = 0;
    const int pause = 1;

    while(serial->atEnd()){
        QThread::currentThread()->msleep(pause);
        time += pause;

        if (time >= timeout){
            return;
        }
    }

    while(!serial->atEnd()){
        QThread::currentThread()->msleep(pause);
        time += pause;

        if (time >= timeout){
            return;
        }
    }
}

void UART::clearRXBuffer()
{
    QThread::currentThread()->msleep(1);
    serial->clear();
    for (int i = 0; i < rx_buffer_index; i++){
        rx_buffer[i] = 0;
    }
    rx_buffer_index = 0;
}
