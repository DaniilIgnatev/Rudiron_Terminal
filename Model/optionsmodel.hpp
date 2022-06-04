#ifndef OPTIONSMODEL_HPP
#define OPTIONSMODEL_HPP

#include <QObject>
#include "TypeDefs.hpp"
#include <QMetaEnum>


class OptionsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DisplayModeEnum displayMode READ getDisplayMode WRITE setDisplayMode NOTIFY displayModeChanged)
    Q_PROPERTY(QString portName READ getPortName WRITE setPortName NOTIFY portNameChanged)
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

    QString _portName;

public:
    DisplayModeEnum getDisplayMode() const;
    void setDisplayMode(DisplayModeEnum newDisplayMode);

    Q_INVOKABLE QString printable();

    QString getPortName() const;
    void setPortName(const QString &value);

signals:
    void displayModeChanged();
    void portNameChanged();
};


#endif // OPTIONSMODEL_HPP
