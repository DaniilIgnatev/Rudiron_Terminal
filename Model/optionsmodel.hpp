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
    Q_PROPERTY(bool autoScroll READ getAutoScroll WRITE setAutoScroll NOTIFY autoScrollChanged)
    Q_PROPERTY(bool showTimeStamps READ getShowTimeStamps WRITE setShowTimeStamps NOTIFY showTimeStampsChanged)

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

    bool _autoScroll;

    bool _showTimeStamps;

public:
    DisplayModeEnum getDisplayMode() const;
    void setDisplayMode(DisplayModeEnum newDisplayMode);

    Q_INVOKABLE QString printable();

    QString getPortName() const;

    void setPortName(const QString &value);

    bool getAutoScroll() const;
    void setAutoScroll(bool value);

    bool getShowTimeStamps() const;
    void setShowTimeStamps(bool value);

signals:
    void displayModeChanged();
    void portNameChanged();
    void autoScrollChanged();
    void showTimeStampsChanged();
};


#endif // OPTIONSMODEL_HPP
