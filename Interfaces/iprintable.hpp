#ifndef IPRINTABLE_H
#define IPRINTABLE_H

#include "TypeDefs.hpp"

class IPrintable {
public:
    Q_INVOKABLE virtual QString printable() = 0;
};


#endif // IPRINTABLE_H
