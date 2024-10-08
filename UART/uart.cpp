#include "uart.hpp"
#include <QThread>
#include <QMetaEnum>

#include <QCoreApplication>


UART::UART(QObject *parent)
    : QObject{parent}
{
    serial = new QSerialPort(this);
}

QString UART::getCurrentPortName()
{
    return serial->portName();
}

bool UART::isOpen()
{
    return serial->isOpen();
}

int UART::getByte(int at)
{
    return this->rx_buffer[at];
}

bool UART::begin(QSerialPortInfo port)
{
    end();

    serial->deleteLater();
    serial = new QSerialPort(port, this);

    connect(serial, &QSerialPort::errorOccurred, this, &UART::errorSlot);
    connect(serial, &QSerialPort::readyRead, this, &UART::readyReadSlot);

    if (!serial->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections)){
        return false;
    }
    if (!serial->setDataBits(QSerialPort::Data8)){
        return false;
    }
    if (!serial->setParity(QSerialPort::NoParity)){
        return false;
    }
    if (!serial->setStopBits(QSerialPort::OneStop)){
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

bool UART::begin(OptionsInputModel *model)
{
    end();

    serial->deleteLater();
    QString portName = model->getPortName();
    serial = new QSerialPort(portName);

    connect(serial, &QSerialPort::errorOccurred, this, &UART::errorSlot);
    connect(serial, &QSerialPort::readyRead, this, &UART::readyReadSlot);

    if (!serial->setBaudRate(model->getBaudRate(), QSerialPort::AllDirections)){
        return false;
    }
    QSerialPort::DataBits bits = (QSerialPort::DataBits)model->getDataBits();
    if (!serial->setDataBits(bits)){
        return false;
    }
    if (!serial->setParity(model->getParity())){
        return false;
    }
    QSerialPort::StopBits stops = model->getStopBits();
    if (!serial->setStopBits(stops)){
        return false;
    }
    if (!serial->setFlowControl(model->getFlowControl())){
        return false;
    }

    if (!serial->open(QIODevice::ReadWrite)) {
        return false;
    }

    while(!serial->isOpen()){
        QThread::currentThread()->msleep(5);
    }
    clearRXBuffer();

    return true;
}

void UART::end()
{
    if (serial){
        serial->clear();
        serial->clearError();
        serial->close();
    }
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
void UART::writeRead(QByteArray buffer, int waitRXBytes)
{
    int count_target = this->rx_buffer.count() + waitRXBytes;

    serial->write(buffer);
    serial->waitForBytesWritten();
    serial->waitForReadyRead(1);

    if (waitRXBytes){
        while (rx_buffer.count() < count_target){
            serial->waitForReadyRead(0);
        }
        while (rx_buffer.count() > count_target) {
            rx_buffer.remove(rx_buffer.count() - 1, 1);
        }
    }
}
#else
void UART::writeRead(QByteArray buffer, int waitRXBytes)
{
    if (waitRXBytes > 0){
        serial->write(buffer);
        serial->waitForReadyRead(read_delay);

        while (rx_buffer.count()  < waitRXBytes){
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

void UART::readyReadSlot()
{
    emit available(serial->readAll());
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
    rx_buffer.clear();
    serial->clear();
}

QByteArray UART::getRXBuffer()
{
    return QByteArray(rx_buffer);
}

QStringList UART::availablePortNames()
{
    QStringList names;
    auto ports = QSerialPortInfo::availablePorts();

    foreach (auto port, ports){
        names.append(port.portName());
    }

    return names;
}
