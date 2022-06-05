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
    return optionsModelDelegate->getOptionsModel();
}

void LogVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    optionsModelDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *LogVM::getOptionsModelDelegate() const
{
    return optionsModelDelegate;
}

void LogVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    optionsModelDelegate = newDisplayModeDelegate;
    connect(optionsModelDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &LogVM::optionsModelChanged);
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
    receivedPackages.clear();
    _logReplaced = true;
    emit logReplaced(getLog());
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

bool LogVM::getLogReplaced() const
{
    return _logReplaced;
}

void LogVM::setLogReplaced(bool newValue)
{
    _logReplaced = newValue;
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
    if (getOptionsModel()->getShowTimeStamps()){
        text.append(QString::number(package->getDateTime().time().hour()));
        text.append(":");
        text.append(QString::number(package->getDateTime().time().minute()));
        text.append(":");
        text.append(QString::number(package->getDateTime().time().second()));
        text.append(":");
        text.append(QString::number(package->getDateTime().time().msec()));
        text.append(" -> ");
    }

    text.append(package->getData());
    return text;
}

void LogVM::onOptionsModelChanged(OptionsModel *newValue)
{
    if (_lastDisplayMode != newValue->getDisplayMode() || _lastShowTimeStamps != newValue->getShowTimeStamps()){
        _lastDisplayMode = newValue->getDisplayMode();
        _lastShowTimeStamps = newValue->getShowTimeStamps();
        emit logReplaced(getLog());
    }
}
