#include "terminalvm.hpp"

TerminalVM::TerminalVM(QObject *parent)
    : IDisplayMode{parent}
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

    transmitterVM->setDisplayModeDelegate(this);
    logVM->setDisplayModeDelegate(this);
    optionsVM->setDisplayModeDelegate(this);
}

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

IDisplayMode::Enum TerminalVM::getDisplayMode()
{
    return this->displayMode;
}

void TerminalVM::setDisplayMode(IDisplayMode::Enum newDisplayMode)
{
    if (displayMode == newDisplayMode)
        return;
    displayMode = newDisplayMode;
    emit displayModeChanged(newDisplayMode);
}
