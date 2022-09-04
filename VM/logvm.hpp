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

public:
    const int receivedPackages_maxCount = 500;

private:
    QList<UARTPackage*> pack_data(const QByteArray rx_buffer_data);

    QByteArray appendLastPackageData(QList<UARTPackage*> &appendPackages, UARTPackage* lastPackage, bool &lastPackageValid);

    QString fillLog(QList<UARTPackage*> logPackages);

    QList<UARTPackage*> receivedPackages;

    QList<UARTPackage*> addPackages(QList<UARTPackage*> packages);

    UARTPackage* addPackage(UARTPackage* package);

    QString remove(QList<UARTPackage *> packages);

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

    Q_INVOKABLE virtual void output(QString message) override;
    virtual void clear() override;

private slots:
    void uartAvailable(const QByteArray incomeData);

signals:
    void logAdded(QString appendedLog, QString removedLog);
    void logReplaced(QString newlog);

public slots:

    QString getLog();

private:
    QString convertToLog(QList<UARTPackage*> packages);

    QString convertToLog(const UARTPackage* package);

    QString convertToLog(const QByteArray data);

    QString convertPackageAsText(const QByteArray package);

    QString getPackageLabel(const UARTPackage* package);

protected slots:
    virtual void onOptionsModelChanged() override;
};

#endif // LOGVM_H
