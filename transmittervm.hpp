#ifndef TRANSMITTERVM_HPP
#define TRANSMITTERVM_HPP

#include <QObject>
#include "uart.hpp"
#include "displaymode.h"


class TransmitterVM : public QObject, IDisplayMode
{
    Q_OBJECT
private:
    UART* uart;

public:
    explicit TransmitterVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual void setDisplayMode(DisplayMode::Enum mode) override;
    virtual DisplayMode::Enum getDisplayMode() override;

signals:

public slots:
    void send(QString text);
};

#endif // TRANSMITTERVM_HPP
