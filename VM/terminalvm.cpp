#include "terminalvm.hpp"

TerminalVM::TerminalVM(QObject *parent)
    : IOptionsModelDelegate{parent}
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

    transmitterVM->setOptionsModelDelegate(this);
    logVM->setOptionsModelDelegate(this);
    optionsVM->setOptionsModelDelegate(this);

    OptionsModel *optionsModel = new OptionsModel(this);
    this->optionsModel = optionsModel;
    emit optionsModelChanged(optionsModel);
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

OptionsModel* TerminalVM::getOptionsModel()
{
    return this->optionsModel;
}

void TerminalVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    optionsModel = newOptionsModel;
    emit optionsModelChanged(newOptionsModel);
}
