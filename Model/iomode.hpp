#ifndef IOMODE_HPP
#define IOMODE_HPP

#include "TypeDefs.hpp"
#include <QMetaEnum>

class IOMode : public QObject
{
    Q_OBJECT
public:
    enum Enum{
        TEXT,
        BIN,
        OCT,
        DEC,
        HEX
    };
    Q_ENUM(IOMode::Enum)

    explicit IOMode(QObject *parent = nullptr);
};

typedef IOMode::Enum IOModeEnum;

#endif // IOMODE_HPP
