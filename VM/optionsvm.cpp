#include "optionsvm.hpp"

OptionsVM::OptionsVM(QObject *parent): IOptionsModelDelegate{parent}
{

}

UART *OptionsVM::getUart() const
{
    return uart;
}

void OptionsVM::setUart(UART *newUart)
{
    uart = newUart;
}

OptionsModel* OptionsVM::getOptionsModel()
{
    return displayModeDelegate->getOptionsModel();
}

void OptionsVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    displayModeDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *OptionsVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void OptionsVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &OptionsVM::optionsModelChanged);
}
