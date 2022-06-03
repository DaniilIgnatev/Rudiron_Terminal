#ifndef IOPTIONSMODELDELEGATEHOLDERHPP_H
#define IOPTIONSMODELDELEGATEHOLDERHPP_H

#include "ioptionsmodeldelegate.hpp"


class IOptionsModelDelegateHolder{
public:
    virtual IOptionsModelDelegate *getDisplayModeDelegate() const = 0;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) = 0;
};

#endif // IOPTIONSMODELDELEGATEHOLDERHPP_H
