#include "terminalvm.hpp"

TerminalVM::TerminalVM(QObject *parent)
    : IOptionsModelDelegate{parent}
{
    transmitterVM->setUart(uart);
    logVM->setUart(uart);
    optionsVM->setUart(uart);

    transmitterVM->setOptionsModelDelegate(this);
    transmitterVM->setOutputDelegate((IOutputDelegate*)logVM);
    logVM->setOptionsModelDelegate(this);
    optionsVM->setOptionsModelDelegate(this);
    optionsVM->setOutputDelegate((IOutputDelegate*)logVM);

    OptionsOutputModel* optionsOutputModel = new OptionsOutputModel(true, true, IOModeEnum::TEXT);
    OptionsInputModel* optionsInputModel = new OptionsInputModel();

    OptionsModel *optionsModel = new OptionsModel(optionsOutputModel, "", optionsInputModel, this);
    connect(optionsModel, &OptionsModel::objectHasChanged, this, &TerminalVM::optionsModelChanged);
    connect(this, &TerminalVM::optionsModelChanged, this, &TerminalVM::onOptionsModelChanged);

    this->optionsModel = optionsModel;
    emit optionsModelChanged();
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
    emit optionsModelChanged();
}
