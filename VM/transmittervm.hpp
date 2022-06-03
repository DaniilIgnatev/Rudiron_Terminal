#ifndef TRANSMITTERVM_HPP
#define TRANSMITTERVM_HPP

#include <QObject>
#include "uart.hpp"
#include "displaymode.h"


class TransmitterVM : public IDisplayMode
{
    Q_OBJECT
private:
    UART* uart;

    IDisplayMode* displayModeDelegate = nullptr;

public:
    explicit TransmitterVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual IDisplayMode::Enum getDisplayMode() override;
    virtual void setDisplayMode(IDisplayMode::Enum newDisplayMode) override;

    IDisplayMode *getDisplayModeDelegate() const;
    void setDisplayModeDelegate(IDisplayMode *newDisplayModeDelegate);

signals:

public slots:
    void send(QString text);
};

#endif // TRANSMITTERVM_HPP
