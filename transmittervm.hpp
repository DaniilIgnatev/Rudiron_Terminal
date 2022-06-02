#ifndef TRANSMITTERVM_HPP
#define TRANSMITTERVM_HPP

#include <QObject>
#include "uart.hpp"


class TransmitterVM : public QObject
{
    Q_OBJECT
private:
    UART* uart;

public:
    explicit TransmitterVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

signals:

public slots:
    void send(QString text);
};

#endif // TRANSMITTERVM_HPP
