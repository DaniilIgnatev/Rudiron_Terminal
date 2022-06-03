#include "optionsmodel.hpp"


OptionsModel::OptionsModel(QObject *parent) : QObject(parent)
{

}

OptionsModel::DisplayModeEnum OptionsModel::getDisplayMode() const
{
    return _displayMode;
}

void OptionsModel::setDisplayMode(DisplayModeEnum newDisplayMode)
{
    if (_displayMode == newDisplayMode)
        return;
    _displayMode = newDisplayMode;
    emit displayModeChanged();
}

QString OptionsModel::printable()
{
    QMetaEnum metaEnum = QMetaEnum::fromType<OptionsModel::DisplayModeEnum>();

    QString text;
    text += "Display mode: " + QString(metaEnum.valueToKey(_displayMode));
    return text;
}
