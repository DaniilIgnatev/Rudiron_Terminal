#ifndef LOGVM_H
#define LOGVM_H

#include <QObject>
#include "uart.hpp"
#include "uartpackage.h"
#include "TypeDefs.hpp"
#include "displaymode.h"


class LogVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DisplayModeEnum displayMode READ getDisplayMode WRITE setDisplayMode NOTIFY displayModeChanged)
private:
    UART* uart;

    QList<UARTPackage*> receivedPackages;

public:
    explicit LogVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

signals:
    void logAppended(QString appendedLog);

    void displayModeChanged();

private slots:

    void uartAvailable();

public slots:

    QString getLog();

    DisplayMode::Enum getDisplayMode() const;
    void setDisplayMode(DisplayMode::Enum newDisplayMode);

private:
    QString convertToLog(const UARTPackage* package);

    QString convertPackageAsText(const UARTPackage* package);

};

#endif // LOGVM_H
