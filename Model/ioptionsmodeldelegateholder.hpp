#ifndef IOPTIONSMODELDELEGATEHOLDERHPP_H
#define IOPTIONSMODELDELEGATEHOLDERHPP_H

#include "ioptionsmodeldelegate.hpp"


class IOptionsModelDelegateHolder: public IOptionsModelDelegate {
public:
    IOptionsModelDelegateHolder(QObject* parent = nullptr): IOptionsModelDelegate(parent){}

    virtual IOptionsModelDelegate *getOptionsModelDelegate() const = 0;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) = 0;
};

#endif // IOPTIONSMODELDELEGATEHOLDERHPP_H
