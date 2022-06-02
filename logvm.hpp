#ifndef LOGVM_H
#define LOGVM_H

#include <QObject>
#include "uart.hpp"
#include "TypeDefs.hpp"


class LogVM_Package : public QObject{
    Q_OBJECT
    Q_PROPERTY(QDateTime dateTime READ getDateTime CONSTANT)
    Q_PROPERTY(QByteArray data READ getData CONSTANT)
public:
    QByteArray data;

    QDateTime dateTime;
    const QDateTime &getDateTime() const;
    const QByteArray &getData() const;
};


class LogVM : public QObject
{
    Q_OBJECT
public:
    enum DisplayModeEnum{
        TEXT,
        HEX,
        DEC,
        OCT,
        BIN
    };
    Q_ENUM(DisplayModeEnum)

private:
    UART* uart;

    QList<LogVM_Package*> receivedPackages;

public:
    explicit LogVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

signals:
    void newPackageReceived(LogVM_Package* package);

private slots:

    void uartAvailable();

public slots:

    QString getLog(LogVM::DisplayModeEnum mode);

private:
    QString getLogAsText();
};

#endif // LOGVM_H
