#ifndef TRANSMITTERVM_HPP
#define TRANSMITTERVM_HPP

#include <QObject>
#include "uart.hpp"
#include "ioptionsmodeldelegate.hpp"
#include "ioptionsmodeldelegateholder.hpp"


class TransmitterVM : public IOptionsModelDelegateHolder
{
    Q_OBJECT
private:
    UART* uart;

    IOptionsModelDelegate* displayModeDelegate = nullptr;

public:
    explicit TransmitterVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual OptionsModel *getOptionsModel() override;
    virtual void setOptionsModel(OptionsModel *newDisplayMode) override;

    virtual IOptionsModelDelegate *getDisplayModeDelegate() const override;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) override;

signals:

public slots:
    void send(QString text);
};

#endif // TRANSMITTERVM_HPP
