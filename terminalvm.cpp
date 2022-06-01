#include "terminalvm.hpp"

TransmitterVM *TerminalVM::getTransmitter() const
{
    return transmitter;
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
    transmitter->setUart(uart);
}
