#ifndef OPTIONSMODEL_HPP
#define OPTIONSMODEL_HPP

#include <QObject>
#include "TypeDefs.hpp"
#include <QMetaEnum>


class OptionsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DisplayModeEnum displayMode READ getDisplayMode WRITE setDisplayMode NOTIFY displayModeChanged)
public:
    explicit OptionsModel(QObject* parent = nullptr);

    enum DisplayModeEnum{
        TEXT,
        HEX,
        DEC,
        OCT,
        BIN
    };
    Q_ENUM(DisplayModeEnum)
private:
    DisplayModeEnum _displayMode;

public:
    DisplayModeEnum getDisplayMode() const;
    void setDisplayMode(DisplayModeEnum newDisplayMode);

    Q_INVOKABLE QString printable();

signals:
    void displayModeChanged();
};


#endif // OPTIONSMODEL_HPP
