#ifndef IOUTPUTDELEGATEHOLDER_H
#define IOUTPUTDELEGATEHOLDER_H

#include "ioutputdelegate.hpp"

class IOutputDelegateHolder{
public:
    virtual IOutputDelegate *getOutputDelegate() const = 0;
    virtual void setOutputDelegate(IOutputDelegate *newOutputDelegate) = 0;
};

#endif // IOUTPUTDELEGATEHOLDER_H
