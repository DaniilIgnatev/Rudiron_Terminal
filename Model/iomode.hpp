#ifndef IOMODE_HPP
#define IOMODE_HPP

#include "TypeDefs.hpp"
#include <QMetaEnum>

class IOMode : public QObject
{
    Q_OBJECT
public:
    enum IOModeEnum{
        TEXT,
        BIN,
        OCT,
        DEC,
        HEX
    };
    Q_ENUM(IOModeEnum)

    explicit IOMode(QObject *parent = nullptr);
};

typedef IOMode::IOModeEnum IOModeEnum;

#endif // IOMODE_HPP
