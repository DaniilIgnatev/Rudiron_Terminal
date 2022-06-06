#include "optionsmodel.hpp"


OptionsModel::OptionsModel(QObject *parent) : IObservable(parent)
{
    connect(this, &OptionsModel::outputModelChanged, this, &OptionsModel::objectHasChanged);
    connect(this, &OptionsModel::portNameChanged, this, &OptionsModel::objectHasChanged);
}

OptionsModel::OptionsModel(OptionsOutputModel* outputModel, QString portName, QObject *parent) : OptionsModel(parent)
{
    _outputModel = outputModel;
    _outputModel->setParent(this);
    _portName = portName;
}

OptionsOutputModel *OptionsModel::getOutputModel() const
{
    return _outputModel;
}

void OptionsModel::setOutputModel(OptionsOutputModel *newOutputModel)
{
    if (_outputModel == newOutputModel)
        return;
    _outputModel = newOutputModel;
    emit outputModelChanged();
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

QString OptionsModel::printable()
{
    QString text;
    text += getOutputModel()->printable();
    text += "Port name: " + _portName + "\n";

    return text;
}
