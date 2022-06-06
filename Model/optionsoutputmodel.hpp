#ifndef OPTIONSOUTPUTMODEL_HPP
#define OPTIONSOUTPUTMODEL_HPP

#include "iomode.hpp"
#include "iprintable.hpp"
#include "iobservable.hpp"


class OptionsOutputModel : public IObservable, public IPrintable
{
    Q_OBJECT
    Q_PROPERTY(bool autoScroll READ getAutoScroll WRITE setAutoScroll NOTIFY autoScrollChanged)
    Q_PROPERTY(bool showTimeStamps READ getShowTimeStamps WRITE setShowTimeStamps NOTIFY showTimeStampsChanged)
    Q_PROPERTY(IOModeEnum mode READ getMode WRITE setMode NOTIFY modeChanged)
public:
    explicit OptionsOutputModel(QObject *parent = nullptr);
    explicit OptionsOutputModel(bool autoScroll, bool showTimeStamps, IOModeEnum mode, QObject *parent = nullptr);

private:
    bool _autoScroll = false;

    bool _showTimeStamps = false;

    IOModeEnum _mode = IOModeEnum::TEXT;

public:
    bool getAutoScroll() const;
    void setAutoScroll(bool value);

    bool getShowTimeStamps() const;
    void setShowTimeStamps(bool value);

    IOModeEnum getMode() const;
    void setMode(IOModeEnum newDisplayMode);

    Q_INVOKABLE virtual QString printable() override;

signals:
    void autoScrollChanged();
    void showTimeStampsChanged();
    void modeChanged();
};

#endif // OPTIONSOUTPUTMODEL_HPP
