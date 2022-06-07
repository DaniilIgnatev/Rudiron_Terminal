#include "ioptionsmodeldelegate.hpp"

IOptionsModelDelegate::IOptionsModelDelegate(QObject *parent): ObservableQObject(parent)
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

void IOptionsModelDelegate::onOptionsModelChanged()
{

}
