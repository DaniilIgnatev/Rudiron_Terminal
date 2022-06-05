#ifndef IOUTPUTDELEGATE_H
#define IOUTPUTDELEGATE_H

#include "TypeDefs.hpp"

class IOutputDelegate{
public:
    Q_INVOKABLE virtual void output(QString message) = 0;

    Q_INVOKABLE virtual void clear() = 0;
};

#endif // IOUTPUTDELEGATE_H
