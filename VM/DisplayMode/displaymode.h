#ifndef DISPLAYMODE_H
#define DISPLAYMODE_H

#include <QObject>


class IDisplayMode : public QObject{
    Q_OBJECT
    Q_PROPERTY(IDisplayMode::Enum displayMode READ getDisplayMode WRITE setDisplayMode NOTIFY displayModeChanged)

public:
    enum Enum{
        TEXT,
        HEX,
        DEC,
        OCT,
        BIN
    };
    Q_ENUM(Enum)

    explicit IDisplayMode(QObject* parent = nullptr): QObject(parent){};
    virtual IDisplayMode::Enum getDisplayMode(){ return IDisplayMode::Enum::TEXT; };
    virtual void setDisplayMode(IDisplayMode::Enum newDisplayMode){ Q_UNUSED(newDisplayMode) };
signals:
    void displayModeChanged(IDisplayMode::Enum newValue);
};

#endif // DISPLAYMODE_H
