#include "ioptionsmodeldelegate.hpp"

IOptionsModelDelegate::IOptionsModelDelegate(QObject *parent): QObject(parent)
{

}

OptionsModel* IOptionsModelDelegate::getOptionsModel()
{
    return nullptr;
}

void IOptionsModelDelegate::setOptionsModel(OptionsModel* newModel)
{
    Q_UNUSED(newModel)
}

void IOptionsModelDelegate::onOptionsModelChanged(OptionsModel *newValue)
{
    Q_UNUSED(newValue)
}
