#ifndef TERMINALVM_H
#define TERMINALVM_H

#include <QObject>

#include "transmittervm.hpp"
#include "logvm.hpp"
#include "optionsvm.hpp"

class TerminalVM : public IOptionsModelDelegate
{
    Q_OBJECT
private:
    UART* uart = new UART(this);

    TransmitterVM* transmitterVM = new TransmitterVM(this);

    LogVM* logVM = new LogVM(this);

    OptionsVM* optionsVM = new OptionsVM(this);

    OptionsModel* optionsModel = nullptr;

public:
    explicit TerminalVM(QObject *parent = nullptr);

    virtual OptionsModel* getOptionsModel() override;
    virtual void setOptionsModel(OptionsModel* newDisplayMode) override;

signals:

protected slots:
    virtual void onOptionsModelChanged() override;

public slots:
   TransmitterVM *getTransmitterVM();

   LogVM *getLogVM();

   OptionsVM *getOptionsVM();

};

#endif // TERMINALVM_H
