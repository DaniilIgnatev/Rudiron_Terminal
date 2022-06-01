#ifndef TERMINALVM_H
#define TERMINALVM_H

#include <QObject>
#include "transmittervm.hpp"


class TerminalVM : public QObject
{
    Q_OBJECT
private:
    UART* uart = new UART(this);

    TransmitterVM* transmitter = new TransmitterVM(this);

public:
    explicit TerminalVM(QObject *parent = nullptr);



signals:

public slots:
    TransmitterVM *getTransmitter() const;

};

#endif // TERMINALVM_H
