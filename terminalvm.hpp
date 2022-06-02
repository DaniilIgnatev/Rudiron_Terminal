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

    TransmitterVM* transmitterVM = new TransmitterVM(this);

    LogVM* logVM = new LogVM(this);

    OptionsVM* optionsVM = new OptionsVM(this);

public:
    explicit TerminalVM(QObject *parent = nullptr);



signals:


public slots:
   TransmitterVM *getTransmitterVM();

   LogVM *getLogVM();

   OptionsVM *getOptionsVM();

};

#endif // TERMINALVM_H
