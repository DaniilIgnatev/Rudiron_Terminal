#ifndef LOGVM_H
#define LOGVM_H

#include <QObject>
#include "uart.hpp"


class LogVM : public QObject
{
    Q_OBJECT
private:
    UART* uart;

public:
    explicit LogVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

signals:

};

#endif // LOGVM_H
