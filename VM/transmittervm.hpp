#ifndef TRANSMITTERVM_HPP
#define TRANSMITTERVM_HPP

#include <QObject>
#include "uart.hpp"
#include "ioptionsmodeldelegateholder.hpp"
#include "ioutputdelegateholder.hpp"

class TransmitterVM : public IOptionsModelDelegateHolder, public IOutputDelegateHolder
{
    Q_OBJECT
private:
    UART* uart;

    IOptionsModelDelegate* optionsModelDelegate = nullptr;

    IOutputDelegate* outputDelegate = nullptr;

public:
    explicit TransmitterVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual OptionsModel *getOptionsModel() override;
    virtual void setOptionsModel(OptionsModel *newDisplayMode) override;

    virtual IOptionsModelDelegate *getOptionsModelDelegate() const override;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) override;

    virtual void output(QString message) override;
    virtual void clear() override;
    virtual IOutputDelegate *getOutputDelegate() const override;
    virtual void setOutputDelegate(IOutputDelegate *newOutputDelegate) override;

signals:

protected slots:
    virtual void onOptionsModelChanged() override;

public slots:
    void send(QString text);
};

#endif // TRANSMITTERVM_HPP
