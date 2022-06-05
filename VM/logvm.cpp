#include "logvm.hpp"

LogVM::LogVM(QObject *parent)
    : IOptionsModelDelegateHolder{parent}
{

}

UART *LogVM::getUart() const
{
    return uart;
}

void LogVM::setUart(UART *newUart)
{
    uart = newUart;
    connect(uart, &UART::available, this, &LogVM::uartAvailable);
}

OptionsModel* LogVM::getOptionsModel()
{
    return displayModeDelegate->getOptionsModel();
}

void LogVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    displayModeDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *LogVM::getDisplayModeDelegate() const
{
    return displayModeDelegate;
}

void LogVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    displayModeDelegate = newDisplayModeDelegate;
    connect(displayModeDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &LogVM::optionsModelChanged);
}

void LogVM::output(QString message)
{
    qDebug() << message;
    emit logAppended(message);
    if (!message.endsWith('\n')){
        qDebug() << "\n";
        emit logAppended("\n");
    }
}

void LogVM::clear()
{
    emit logCleared();
}

void LogVM::uartAvailable()
{
    UARTPackage* package = new UARTPackage();
    package->setData(uart->getRXBuffer());
    package->setDateTime(QDateTime::currentDateTime());
    uart->clearRXBuffer();
    receivedPackages.append(package);

    QString appendedLog = convertToLog(package);
    emit logAppended(appendedLog);
}

QString LogVM::getLog()
{
    QString log;
    for(int i = 0; i < receivedPackages.count(); i++){
        auto package = receivedPackages.at(i);
        log += convertToLog(package);
    }

    return log;
}

QString LogVM::convertToLog(const UARTPackage* package)
{
    switch (getOptionsModel()->getDisplayMode()) {
        case OptionsModel::DisplayModeEnum::TEXT:
        return convertPackageAsText(package);
    default:
        return convertPackageAsText(package);
    }
}

QString LogVM::convertPackageAsText(const UARTPackage* package)
{
    QString text;
    text.append(QString::number(package->getDateTime().time().hour()));
    text.append(":");
    text.append(QString::number(package->getDateTime().time().minute()));
    text.append(":");
    text.append(QString::number(package->getDateTime().time().second()));
    text.append(":");
    text.append(QString::number(package->getDateTime().time().msec()));
    text.append(" -> ");
    text.append(package->getData());
    return text;
}
