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
    Q_PROPERTY(DisplayModeEnum displayMode READ getDisplayMode WRITE setDisplayMode NOTIFY displayModeChanged)
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

    DisplayModeEnum displayMode = DisplayModeEnum::TEXT;

public:
    explicit LogVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    DisplayModeEnum getDisplayMode() const;

    void setDisplayMode(DisplayModeEnum newDisplayMode);

signals:
    void logAppended(QString appendedLog);

    void displayModeChanged();

private slots:

    void uartAvailable();

public slots:

    QString getLog();

private:
    QString convertToLog(const LogVM_Package* package);

    QString convertPackageAsText(const LogVM_Package* package);

};

#endif // LOGVM_H
