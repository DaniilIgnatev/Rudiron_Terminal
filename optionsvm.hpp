#ifndef OPTIONSVM_HPP
#define OPTIONSVM_HPP

#include <QObject>
#include "uart.hpp"


class OptionsVM : public QObject
{
    Q_OBJECT
private:
    UART* uart;

public:
    explicit OptionsVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

signals:

};

#endif // OPTIONSVM_HPP
