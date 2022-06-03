#ifndef UARTPACKAGE_H
#define UARTPACKAGE_H

#include <QObject>
#include "TypeDefs.hpp"

class UARTPackage : public QObject{
    Q_OBJECT
    Q_PROPERTY(QByteArray data READ getData WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QDateTime dateTime READ getDateTime WRITE setDateTime NOTIFY dateTimeChanged)

private:
    QByteArray _data;
    QDateTime _dateTime;

public:
    explicit UARTPackage(QObject* object = nullptr);

    const QByteArray &getData() const;
    void setData(const QByteArray &newData);

    const QDateTime &getDateTime() const;
    void setDateTime(const QDateTime &newDateTime);

signals:
    void dataChanged();
    void dateTimeChanged();
};

#endif // UARTPACKAGE_H
