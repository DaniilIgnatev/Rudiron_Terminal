#ifndef OPTIONSVM_HPP
#define OPTIONSVM_HPP

#include <QObject>
#include "uart.hpp"
#include "displaymode.h"


class OptionsVM : public IDisplayMode
{
    Q_OBJECT
private:
    UART* uart;

    IDisplayMode* displayModeDelegate = nullptr;

public:
    explicit OptionsVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual IDisplayMode::Enum getDisplayMode() override;
    virtual void setDisplayMode(IDisplayMode::Enum newDisplayMode) override;

    IDisplayMode *getDisplayModeDelegate() const;
    void setDisplayModeDelegate(IDisplayMode *newDisplayModeDelegate);

signals:

};

#endif // OPTIONSVM_HPP
