#include "terminalvm.hpp"

TerminalVM::TerminalVM(QObject *parent)
    : IOptionsModelDelegate{parent}
{
    transmitterVM->setUart(uart);
    logVM->setUart(uart);
    optionsVM->setUart(uart);

    transmitterVM->setOptionsModelDelegate(this);
    logVM->setOptionsModelDelegate(this);
    optionsVM->setOptionsModelDelegate(this);
    optionsVM->setOutputDelegate((IOutputDelegate*)logVM);

    OptionsModel *optionsModel = new OptionsModel(this);
    optionsModel->setPortName("");
    optionsModel->setDisplayMode(OptionsModel::DisplayModeEnum::TEXT);
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
