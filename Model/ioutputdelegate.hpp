#ifndef IOUTPUTDELEGATE_H
#define IOUTPUTDELEGATE_H

#include "TypeDefs.hpp"

class IOutputDelegate{
public:
    virtual void output(QString message) = 0;

    virtual void clear() = 0;
};

#endif // IOUTPUTDELEGATE_H
