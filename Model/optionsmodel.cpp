#include "optionsmodel.hpp"


OptionsModel::OptionsModel(QObject *parent) : QObject(parent)
{

}

bool OptionsModel::getAutoScroll() const
{
    return _autoScroll;
}

void OptionsModel::setAutoScroll(bool value)
{
    if (_autoScroll == value)
        return;
    _autoScroll = value;
    emit autoScrollChanged();
}

bool OptionsModel::getShowTimeStamps() const
{
    return _showTimeStamps;
}

void OptionsModel::setShowTimeStamps(bool value)
{
    if (_showTimeStamps == value)
        return;
    _showTimeStamps = value;
    emit showTimeStampsChanged();
}

QString OptionsModel::getPortName() const
{
    return _portName;
}

void OptionsModel::setPortName(const QString &value)
{
    if (_portName == value)
        return;
    _portName = value;
    emit portNameChanged();
}

OptionsModel::DisplayModeEnum OptionsModel::getDisplayMode() const
{
    return _displayMode;
}

void OptionsModel::setDisplayMode(DisplayModeEnum value)
{
    if (_displayMode == value)
        return;
    _displayMode = value;
    emit displayModeChanged();
}

QString OptionsModel::printable()
{
    QMetaEnum metaEnum = QMetaEnum::fromType<OptionsModel::DisplayModeEnum>();

    QString text;
    text += "Display mode: " + QString(metaEnum.valueToKey(_displayMode)) + "\n";
    text += "Port name: " + _portName + "\n";
    text += "AutoScroll: " + QString(_autoScroll ? "true" : "false") + "\n";
    text += "ShowTimeStamps: " + QString(_showTimeStamps ? "true" : "false") + "\n";
    return text;
}
