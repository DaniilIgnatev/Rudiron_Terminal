#ifndef UART_HPP
#define UART_HPP

#include "TypeDefs.hpp"
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "optionsinputmodel.hpp"

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

    QString getCurrentPortName();

    bool isOpen();

    int getByte(int at);

    bool begin(QSerialPortInfo port);

    bool begin(OptionsInputModel* model);

    void end();

    void setBaudRate(qint32 rate);

    void writeRead(QByteArray buffer, int readBytes);

    void waitRead(int timeout = 100);

    void clearRXBuffer();

    QByteArray getRXBuffer();

    Q_INVOKABLE QStringList availablePortNames();

signals:

    void available();

public slots:
    void errorSlot(QSerialPort::SerialPortError error);

    void readyReadSlot();
};

#endif // UART_HPP
