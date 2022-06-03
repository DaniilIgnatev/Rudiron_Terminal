#include "terminalvm.hpp"

TransmitterVM *TerminalVM::getTransmitterVM()
{
    return transmitterVM;
}

LogVM *TerminalVM::getLogVM()
{
    return logVM;
}

OptionsVM *TerminalVM::getOptionsVM()
{
    return optionsVM;
}

TerminalVM::TerminalVM(QObject *parent)
    : QObject{parent}
{
    QSerialPortInfo port;
    auto ports = QSerialPortInfo::availablePorts();

    for (auto &p: ports){
        if (p.productIdentifier() == 60000){
            port = p;
            break;
        }
    }

    uart->begin(port);

    transmitterVM->setUart(uart);
    logVM->setUart(uart);
    optionsVM->setUart(uart);
}
