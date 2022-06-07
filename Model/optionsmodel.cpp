#include "optionsmodel.hpp"


OptionsModel::OptionsModel(QObject *parent) : ObservableQObject(parent)
{
    connect(this, &OptionsModel::outputModelChanged, this, &OptionsModel::objectHasChanged);
    connect(this, &OptionsModel::portNameChanged, this, &OptionsModel::objectHasChanged);
    connect(this, &OptionsModel::inputModelChanged, this, &OptionsModel::objectHasChanged);
}

OptionsModel::OptionsModel(OptionsOutputModel* outputModel, QString portName, OptionsInputModel* inputModel, QObject *parent) : OptionsModel(parent)
{
    _outputModel = outputModel;
    _outputModel->setParent(this);

    _portName = portName;

    _inputModel = inputModel;
    _inputModel->setParent(this);
}

OptionsOutputModel *OptionsModel::getOutputModel() const
{
    return _outputModel;
}

void OptionsModel::setOutputModel(OptionsOutputModel *newOutputModel)
{
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

OptionsInputModel *OptionsModel::getInputModel() const
{
    return _inputModel;
}

void OptionsModel::setInputModel(OptionsInputModel *newInputModel)
{
    _inputModel = newInputModel;
    emit inputModelChanged();
}

QString OptionsModel::printable()
{
    QString text;

    text += "[Output model]\n";
    text += getOutputModel()->printable();
    text += "[Serial port]\n";
    text += "Name: " + _portName + "\n";
    text += "[Input model]\n";
    text += getInputModel()->printable();

    return text;
}
