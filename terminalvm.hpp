#ifndef TERMINALVM_H
#define TERMINALVM_H

#include <QObject>

#include "transmittervm.hpp"
#include "logvm.hpp"
#include "optionsvm.hpp"


class TerminalVM : public QObject
{
    Q_OBJECT
private:
    UART* uart = new UART(this);

    TransmitterVM* transmitter = new TransmitterVM(this);

    LogVM* receiver = new LogVM(this);

    OptionsVM* options = new OptionsVM(this);

public:
    explicit TerminalVM(QObject *parent = nullptr);



signals:


public slots:
   TransmitterVM *getTransmitter();

   LogVM *getReceiver();

   OptionsVM *getOptions();

};

#endif // TERMINALVM_H
