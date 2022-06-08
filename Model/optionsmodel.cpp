#include "optionsmodel.hpp"


OptionsModel::OptionsModel(QObject *parent) : ObservableQObject(parent)
{
    connect(this, &OptionsModel::outputModelChanged, this, &OptionsModel::objectHasChanged);
    connect(this, &OptionsModel::inputModelChanged, this, &OptionsModel::objectHasChanged);
}

OptionsModel::OptionsModel(OptionsOutputModel* outputModel, OptionsInputModel* inputModel, QObject *parent) : OptionsModel(parent)
{
    _outputModel = outputModel;
    _outputModel->setParent(this);

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
    text += "[Input model]\n";
    text += getInputModel()->printable();

    return text;
}
