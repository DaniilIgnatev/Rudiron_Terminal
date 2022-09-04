#ifndef UARTPACKAGE_H
#define UARTPACKAGE_H

#include <QObject>
#include "TypeDefs.hpp"

class UARTPackage : public QObject{
    Q_OBJECT
    Q_PROPERTY(QByteArray data READ getData WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QDateTime dateTime READ getDateTime WRITE setDateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(bool isLogOutput READ getIsLogOutput WRITE setIsLogOutput NOTIFY logOutputChanged)
    Q_PROPERTY(QString portName READ getPortName WRITE setPortName NOTIFY portNameChanged)

private:
    QByteArray _data;
    QDateTime _dateTime;
    QString _portName;
    bool _isLogOutput = false;

public:
    explicit UARTPackage(QObject* object = nullptr);

    const QByteArray getData() const;
    void setData(const QByteArray newData);

    const QDateTime &getDateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    bool getIsLogOutput() const;
    void setIsLogOutput(bool value);

    QString getPortName() const;
    void setPortName(const QString &value);

    bool isValid();

signals:
    void dataChanged();
    void dateTimeChanged();
    void logOutputChanged();
    void portNameChanged();
};

#endif // UARTPACKAGE_H
