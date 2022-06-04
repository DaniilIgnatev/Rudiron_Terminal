#ifndef OPTIONSVM_HPP
#define OPTIONSVM_HPP

#include <QObject>
#include "uart.hpp"
#include "ioptionsmodeldelegate.hpp"
#include "ioptionsmodeldelegateholder.hpp"


class OptionsVM : public IOptionsModelDelegate, IOptionsModelDelegateHolder
{
    Q_OBJECT
private:
    UART* uart;

    IOptionsModelDelegate* displayModeDelegate = nullptr;

public:
    explicit OptionsVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual OptionsModel *getOptionsModel() override;
    virtual void setOptionsModel(OptionsModel *newDisplayMode) override;

    virtual IOptionsModelDelegate *getDisplayModeDelegate() const override;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) override;

    Q_INVOKABLE QStringList availablePortNames();

protected slots:
    virtual void onOptionsModelChanged(OptionsModel* newValue) override;

signals:

};

#endif // OPTIONSVM_HPP
