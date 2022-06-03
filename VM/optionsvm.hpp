#ifndef OPTIONSVM_HPP
#define OPTIONSVM_HPP

#include <QObject>
#include "uart.hpp"
#include "displaymode.h"


class OptionsVM : public QObject, IDisplayMode
{
    Q_OBJECT
private:
    UART* uart;

public:
    explicit OptionsVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual void setDisplayMode(DisplayMode::Enum mode) override;
    virtual DisplayMode::Enum getDisplayMode() override;

signals:

};

#endif // OPTIONSVM_HPP
