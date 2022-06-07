#ifndef OPTIONSVM_HPP
#define OPTIONSVM_HPP

#include "TypeDefs.hpp"
#include "uart.hpp"
#include "ioptionsmodeldelegate.hpp"
#include "ioptionsmodeldelegateholder.hpp"
#include "ioutputdelegateholder.hpp"
#include "observableqobject.hpp"


class OptionsVM : public IOptionsModelDelegateHolder, public IOutputDelegateHolder
{
    Q_OBJECT
private:
    UART* uart;

    IOptionsModelDelegate* optionsModelDelegate = nullptr;

    IOutputDelegate* outputDelegate = nullptr;

public:
    explicit OptionsVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual OptionsModel *getOptionsModel() override;
    virtual void setOptionsModel(OptionsModel *newDisplayMode) override;

    virtual IOptionsModelDelegate *getOptionsModelDelegate() const override;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) override;

    virtual void output(QString message) override;
    Q_INVOKABLE virtual void clear() override;
    virtual IOutputDelegate *getOutputDelegate() const override;
    virtual void setOutputDelegate(IOutputDelegate *newOutputDelegate) override;

    Q_INVOKABLE QString getDefaultPortName();
    Q_INVOKABLE QStringList getAvailablePortNames();

protected slots:
    virtual void onOptionsModelChanged() override;

signals:
    void openPortFailure(QString portName);
};

#endif // OPTIONSVM_HPP
