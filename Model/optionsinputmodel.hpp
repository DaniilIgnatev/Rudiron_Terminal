#ifndef OPTIONSINPUTMODEL_HPP
#define OPTIONSINPUTMODEL_HPP

#include "iomode.hpp"
#include "iprintable.hpp"
#include "observableqobject.hpp"
#include "qserialport.h"

class OptionsInputModel : public ObservableQObject, public IPrintable
{
    Q_OBJECT
    Q_PROPERTY(int baudRate READ getBaudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(int dataBits READ getDataBits WRITE setDataBits NOTIFY dataBitsChanged)
    Q_PROPERTY(QSerialPort::Parity parity READ getParity WRITE setParity NOTIFY parityChanged)
    Q_PROPERTY(QSerialPort::StopBits stopBits READ getStopBits WRITE setStopBits NOTIFY stopBitsChanged)
    Q_PROPERTY(QSerialPort::FlowControl flowControl READ getFlowControl WRITE setFlowControl NOTIFY flowControlChanged)
    Q_PROPERTY(QString stringEnd READ getStringEnd WRITE setStringEnd NOTIFY stringEndChanged)
    Q_PROPERTY(IOModeEnum mode READ getMode WRITE setMode NOTIFY modeChanged)

private:
    int _baudRate;
    int _dataBits;
    QSerialPort::Parity _parity;
    QSerialPort::StopBits _stopBits;
    QSerialPort::FlowControl _flowControl;
    QString _stringEnd;
    IOModeEnum _mode;

public:
    explicit OptionsInputModel(QObject *parent = nullptr);

    explicit OptionsInputModel(int baudRate,
                               int dataBits,
                               QSerialPort::Parity parity,
                               QSerialPort::StopBits stopBits,
                               QSerialPort::FlowControl flowControl,
                               QString stringEnd,
                               IOModeEnum mode,
                               QObject *parent = nullptr);

    int getBaudRate() const;
    void setBaudRate(int baudRate);

    int getDataBits() const;
    void setDataBits(int dataBits);

    QSerialPort::Parity getParity() const;
    void setParity(const QSerialPort::Parity &parity);

    QSerialPort::StopBits getStopBits() const;
    void setStopBits(const QSerialPort::StopBits &stopBits);

    QSerialPort::FlowControl getFlowControl() const;
    void setFlowControl(const QSerialPort::FlowControl &flowControl);

    QString getStringEnd() const;
    void setStringEnd(const QString &stringEnd);

    IOModeEnum getMode() const;
    void setMode(const IOModeEnum &mode);

    Q_INVOKABLE virtual QString printable() override;

signals:
    void baudRateChanged();
    void dataBitsChanged();
    void parityChanged();
    void stopBitsChanged();
    void flowControlChanged();
    void stringEndChanged();
    void modeChanged();
};

#endif // OPTIONSINPUTMODEL_HPP
