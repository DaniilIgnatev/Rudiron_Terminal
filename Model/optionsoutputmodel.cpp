#include "optionsoutputmodel.hpp"

OptionsOutputModel::OptionsOutputModel(QObject *parent): ObservableQObject{parent}
{
    connect(this, &OptionsOutputModel::autoScrollChanged, this, &OptionsOutputModel::objectHasChanged);
    connect(this, &OptionsOutputModel::showTimeStampsChanged, this, &OptionsOutputModel::objectHasChanged);
    connect(this, &OptionsOutputModel::modeChanged, this, &OptionsOutputModel::objectHasChanged);
}

OptionsOutputModel::OptionsOutputModel(bool autoScroll, bool showTimeStamps, IOModeEnum mode, QObject *parent)
    : OptionsOutputModel{parent}
{
    this->_autoScroll = autoScroll;
    this->_showTimeStamps = showTimeStamps;
    this->_mode = mode;
}

bool OptionsOutputModel::getAutoScroll() const
{
    return _autoScroll;
}

void OptionsOutputModel::setAutoScroll(bool value)
{
    if (_autoScroll == value)
        return;
    _autoScroll = value;
    emit autoScrollChanged();
}

bool OptionsOutputModel::getShowTimeStamps() const
{
    return _showTimeStamps;
}

void OptionsOutputModel::setShowTimeStamps(bool value)
{
    if (_showTimeStamps == value)
        return;
    _showTimeStamps = value;
    emit showTimeStampsChanged();
}

IOModeEnum OptionsOutputModel::getMode() const
{
    return _mode;
}

void OptionsOutputModel::setMode(IOModeEnum value)
{
    if (_mode == value)
        return;
    _mode = value;
    emit modeChanged();
}

QString OptionsOutputModel::printable()
{
    QMetaEnum modeEnum = QMetaEnum::fromType<IOModeEnum>();

    QString text;

    text += "AutoScroll: " + QString(_autoScroll ? "true" : "false") + "\n";
    text += "ShowTimeStamps: " + QString(_showTimeStamps ? "true" : "false") + "\n";
    text += "Mode: " + QString(modeEnum.valueToKey(_mode)) + "\n";

    return text;
}
