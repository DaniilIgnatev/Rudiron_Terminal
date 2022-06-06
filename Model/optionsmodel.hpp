#ifndef OPTIONSMODEL_HPP
#define OPTIONSMODEL_HPP

#include <QObject>
#include "TypeDefs.hpp"
#include <QMetaEnum>


class OptionsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DisplayModeEnum outputMode READ getOutputMode WRITE setOutputMode NOTIFY outputModeChanged)
    Q_PROPERTY(QString portName READ getPortName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(bool autoScroll READ getAutoScroll WRITE setAutoScroll NOTIFY autoScrollChanged)
    Q_PROPERTY(bool showTimeStamps READ getShowTimeStamps WRITE setShowTimeStamps NOTIFY showTimeStampsChanged)

public:
    explicit OptionsModel(QObject* parent = nullptr);

    enum DisplayModeEnum{
        TEXT,
        BIN,
        OCT,
        DEC,
        HEX
    };
    Q_ENUM(DisplayModeEnum)

private:
    DisplayModeEnum _outputMode;

    QString _portName;

    bool _autoScroll;

    bool _showTimeStamps;

public:
    DisplayModeEnum getOutputMode() const;
    void setOutputMode(DisplayModeEnum newDisplayMode);

    Q_INVOKABLE QString printable();

    QString getPortName() const;

    void setPortName(const QString &value);

    bool getAutoScroll() const;
    void setAutoScroll(bool value);

    bool getShowTimeStamps() const;
    void setShowTimeStamps(bool value);

signals:
    void outputModeChanged();
    void portNameChanged();
    void autoScrollChanged();
    void showTimeStampsChanged();
};


#endif // OPTIONSMODEL_HPP
