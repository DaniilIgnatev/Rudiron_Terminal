#include "ioptionsmodeldelegateholder.hpp"


IOptionsModelDelegateHolder::IOptionsModelDelegateHolder(QObject *parent): IOptionsModelDelegate(parent)
{

}

IOptionsModelDelegate *IOptionsModelDelegateHolder::getOptionsModelDelegate() const
{
    return nullptr;
}

void IOptionsModelDelegateHolder::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    Q_UNUSED(newDisplayModeDelegate)
}
