#ifndef UART_HPP
#define UART_HPP

#include "TypeDefs.hpp"
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class UART : public QObject
{
    Q_OBJECT
private:
    int read_delay = 1;

    QSerialPort* serial = nullptr;

    QByteArray rx_buffer;

    int getEventLoopDelay();

public:
    explicit UART(QObject *parent = nullptr);

    int getByte(int at);

    bool begin(QSerialPortInfo port);

    void end();

    void setBaudRate(qint32 rate);

    void writeSync();

    void writeRead(QByteArray buffer, int readBytes);

    void waitRead(int timeout = 100);

    void clearRXBuffer();

    QByteArray getRXBuffer();

signals:

    void available();

public slots:
    void errorSlot(QSerialPort::SerialPortError error);

    void readyReadSlot();
};

#endif // UART_HPP
