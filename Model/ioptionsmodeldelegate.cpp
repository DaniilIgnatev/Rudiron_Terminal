#include "ioptionsmodeldelegate.hpp"

OptionsModel* IOptionsModelDelegate::getOptionsModel()
{
    return nullptr;
}

void IOptionsModelDelegate::setOptionsModel(OptionsModel* newModel)
{
    Q_UNUSED(newModel)
}
