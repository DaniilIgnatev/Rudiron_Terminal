#include "optionsinputmodel.hpp"

OptionsInputModel::OptionsInputModel(QObject *parent) : ObservableQObject(parent)
{
    connect(this, &OptionsInputModel::portNameChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::baudRateChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::dataBitsChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::parityChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::stopBitsChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::flowControlChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::stringEndChanged, this, &OptionsInputModel::objectHasChanged);
    connect(this, &OptionsInputModel::modeChanged, this, &OptionsInputModel::objectHasChanged);
}

OptionsInputModel::OptionsInputModel(int baudRate,
                                     int dataBits,
                                     QSerialPort::Parity parity,
                                     QSerialPort::StopBits stopBits,
                                     QSerialPort::FlowControl flowControl,
                                     QString stringEnd,
                                     IOModeEnum mode,
                                     QObject *parent) : OptionsInputModel(parent)
{
    this->_baudRate = baudRate;
    this->_dataBits = dataBits;
    this->_parity = parity;
    this->_stopBits = stopBits;
    this->_flowControl = flowControl;
    this->_stringEnd = stringEnd;
    this->_mode = mode;
}

QString OptionsInputModel::getPortName() const
{
    return _portName;
}

void OptionsInputModel::setPortName(const QString &value)
{
    if (_portName == value)
        return;
    _portName = value;
    emit portNameChanged();
}

int OptionsInputModel::getBaudRate() const
{
    return _baudRate;
}

void OptionsInputModel::setBaudRate(int baudRate)
{
    _baudRate = baudRate;
    emit baudRateChanged();
}

int OptionsInputModel::getDataBits() const
{
    return _dataBits;
}

void OptionsInputModel::setDataBits(int dataBits)
{
    _dataBits = dataBits;
    emit dataBitsChanged();
}

QSerialPort::Parity OptionsInputModel::getParity() const
{
    return _parity;
}

void OptionsInputModel::setParity(const QSerialPort::Parity &parity)
{
    _parity = parity;
    emit parityChanged();
}

QSerialPort::StopBits OptionsInputModel::getStopBits() const
{
    return _stopBits;
}

void OptionsInputModel::setStopBits(const QSerialPort::StopBits &stopBits)
{
    _stopBits = stopBits;
    emit stopBitsChanged();
}

QSerialPort::FlowControl OptionsInputModel::getFlowControl() const
{
    return _flowControl;
}

void OptionsInputModel::setFlowControl(const QSerialPort::FlowControl &flowControl)
{
    _flowControl = flowControl;
    emit flowControlChanged();
}

QString OptionsInputModel::getStringEnd() const
{
    return _stringEnd;
}

void OptionsInputModel::setStringEnd(const QString &stringEnd)
{
    _stringEnd = stringEnd;
    emit stringEndChanged();
}

IOModeEnum OptionsInputModel::getMode() const
{
    return _mode;
}

void OptionsInputModel::setMode(const IOModeEnum &mode)
{
    _mode = mode;
    emit modeChanged();
}

QString OptionsInputModel::printable()
{
    QMetaEnum parityEnum = QMetaEnum::fromType<QSerialPort::Parity>();
    QMetaEnum stopBitsEnum = QMetaEnum::fromType<QSerialPort::StopBits>();
    QMetaEnum flowControlEnum = QMetaEnum::fromType<QSerialPort::FlowControl>();
    QMetaEnum modeEnum = QMetaEnum::fromType<IOModeEnum>();

    QString text;
    text += "PortName: " + _portName + "\n";
    text += "BaudRate: " + QString::number(_baudRate) + "\n";
    text += "DataBits: " + QString::number(_dataBits) + "\n";
    text += "Parity: " + QString(parityEnum.valueToKey(_parity)) + "\n";
    text += "StopBits: " + QString(stopBitsEnum.valueToKey(_stopBits)) + "\n";
    text += "FlowControl: " + QString(flowControlEnum.valueToKey(_flowControl)) + "\n";
    text += "StringEnd: " + _stringEnd + "\n";
    text += "Mode: " + QString(modeEnum.valueToKey(_mode)) + "\n";

    return text;
}
