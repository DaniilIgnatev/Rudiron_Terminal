#ifndef DISPLAYMODE_H
#define DISPLAYMODE_H

#include <QObject>

class DisplayMode: public QObject{
    Q_OBJECT
public:
    enum Enum{
        TEXT,
        HEX,
        DEC,
        OCT,
        BIN
    };
    Q_ENUM(Enum)
};


class IDisplayMode{
    virtual void setDisplayMode(DisplayMode::Enum mode) = 0;
    virtual DisplayMode::Enum getDisplayMode() = 0;
};

#endif // DISPLAYMODE_H
