#ifndef OPTIONSVM_HPP
#define OPTIONSVM_HPP

#include "TypeDefs.hpp"
#include "uart.hpp"
#include "ioptionsmodeldelegate.hpp"
#include "ioptionsmodeldelegateholder.hpp"
#include "ioutputdelegateholder.hpp"


class OptionsVM : public IOptionsModelDelegateHolder, IOutputDelegateHolder
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
    virtual void clear() override;
    virtual IOutputDelegate *getOutputDelegate() const override;
    virtual void setOutputDelegate(IOutputDelegate *newOutputDelegate) override;

    Q_INVOKABLE QStringList availablePortNames();

protected slots:
    virtual void onOptionsModelChanged(OptionsModel* newValue) override;

signals:

};

#endif // OPTIONSVM_HPP
