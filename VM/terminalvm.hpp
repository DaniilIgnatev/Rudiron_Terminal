#ifndef TERMINALVM_H
#define TERMINALVM_H

#include <QObject>

#include "transmittervm.hpp"
#include "logvm.hpp"
#include "optionsvm.hpp"
#include "displaymode.h"


class TerminalVM : public QObject, IDisplayMode
{
    Q_OBJECT
private:
    UART* uart = new UART(this);

    TransmitterVM* transmitterVM = new TransmitterVM(this);

    LogVM* logVM = new LogVM(this);

    OptionsVM* optionsVM = new OptionsVM(this);

    DisplayMode::Enum displayMode = DisplayMode::Enum::TEXT;

public:
    explicit TerminalVM(QObject *parent = nullptr);

    virtual void setDisplayMode(DisplayMode::Enum mode) override;
    virtual DisplayMode::Enum getDisplayMode() override;

signals:


public slots:
   TransmitterVM *getTransmitterVM();

   LogVM *getLogVM();

   OptionsVM *getOptionsVM();



};

#endif // TERMINALVM_H
