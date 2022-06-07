#ifndef LOGVM_H
#define LOGVM_H

#include <QObject>
#include "uart.hpp"
#include "uartpackage.hpp"
#include "ioptionsmodeldelegateholder.hpp"
#include "ioutputdelegateholder.hpp"

class LogVM : public IOptionsModelDelegateHolder, IOutputDelegate
{
    Q_OBJECT
private:
    UART* uart;

    QList<UARTPackage*> receivedPackages;

    IOptionsModelDelegate* optionsModelDelegate = nullptr;

    IOModeEnum _lastDisplayMode;

    bool _lastShowTimeStamps;

public:
    explicit LogVM(QObject *parent = nullptr);

    UART *getUart() const;
    void setUart(UART *newUart);

    virtual OptionsModel *getOptionsModel() override;
    virtual void setOptionsModel(OptionsModel *newDisplayMode) override;

    virtual IOptionsModelDelegate *getOptionsModelDelegate() const override;
    virtual void setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate) override;

    virtual void output(QString message) override;
    virtual void clear() override;

private slots:
    void uartAvailable();

signals:
    void logAppended(QString appendedLog);
    void logReplaced(QString newlog);

public slots:

    QString getLog();

private:
    QString convertToLog(const UARTPackage* package);

    QString convertPackageAsText(const UARTPackage* package);

protected slots:
    virtual void onOptionsModelChanged() override;
};

#endif // LOGVM_H
