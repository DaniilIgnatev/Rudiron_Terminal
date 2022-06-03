#ifndef LOGVM_H
#define LOGVM_H

#include <QObject>
#include "uart.hpp"
#include "uartpackage.hpp"
#include "displaymode.h"


class LogVM : public IDisplayMode
{
    Q_OBJECT
private:
    UART* uart;

    QList<UARTPackage*> receivedPackages;

    IDisplayMode* displayModeDelegate = nullptr;

public:
    explicit LogVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual IDisplayMode::Enum getDisplayMode() override;
    virtual void setDisplayMode(IDisplayMode::Enum newDisplayMode) override;

    IDisplayMode *getDisplayModeDelegate() const;
    void setDisplayModeDelegate(IDisplayMode *newDisplayModeDelegate);

private slots:
    void uartAvailable();

signals:
    void logAppended(QString appendedLog);

public slots:

    QString getLog();

private:
    QString convertToLog(const UARTPackage* package);

    QString convertPackageAsText(const UARTPackage* package);

};

#endif // LOGVM_H
