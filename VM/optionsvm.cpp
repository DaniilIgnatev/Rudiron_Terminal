#include "optionsvm.hpp"

OptionsVM::OptionsVM(QObject *parent): IDisplayMode{parent}
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

void OptionsVM::setDisplayMode(IDisplayMode::Enum newDisplayMode)
{
    displayModeDelegate->setDisplayMode(newDisplayMode);
}

IDisplayMode::Enum OptionsVM::getDisplayMode()
{
    return displayModeDelegate->getDisplayMode();
}

IDisplayMode *OptionsVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void OptionsVM::setDisplayModeDelegate(IDisplayMode *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IDisplayMode::displayModeChanged, this, &OptionsVM::displayModeChanged);
}
