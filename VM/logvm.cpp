#include "logvm.hpp"

LogVM::LogVM(QObject *parent)
    : IOptionsModelDelegateHolder{parent}
{
    connect(this, &LogVM::optionsModelChanged, this, &LogVM::onOptionsModelChanged);
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
    if (!message.endsWith('\n')){
        message.append("\n");
    }
    qDebug() << message;

    UARTPackage* package = new UARTPackage();
    package->setData(message.toUtf8());
    package->setDateTime(QDateTime::currentDateTime());
    package->setIsLogOutput(true);
    receivedPackages.append(package);

    QString appendedLog = convertToLog(package);
    emit logAppended(appendedLog);
}

void LogVM::clear()
{
    receivedPackages.clear();
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

QString LogVM::convertToLog(const UARTPackage* package)
{
    switch (getOptionsModel()->getOutputModel()->getMode()) {
        case IOModeEnum::TEXT:
        return convertPackageAsText(package);
    default:
        return convertPackageAsText(package);
    }
}

QString LogVM::convertPackageAsText(const UARTPackage* package)
{
    QString text;

    if (getOptionsModel()->getOutputModel()->getShowTimeStamps()){
        text.append(QString::number(package->getDateTime().time().hour()));
        text.append(":");
        text.append(QString::number(package->getDateTime().time().minute()));
        text.append(":");
        text.append(QString::number(package->getDateTime().time().second()));
        text.append(":");
        text.append(QString::number(package->getDateTime().time().msec()));
        text.append(" ");
    }

    if (package->getIsLogOutput()){
        text.append("Терминал -> ");
    }
    else{
        text.append(getOptionsModel()->getPortName());
        text.append(" -> ");
    }

    text.append(package->getData());
    return text;
}

void LogVM::onOptionsModelChanged()
{
    OptionsModel* newValue = getOptionsModel();
    if (_lastDisplayMode != newValue->getOutputModel()->getMode() || _lastShowTimeStamps != newValue->getOutputModel()->getShowTimeStamps()){
        _lastDisplayMode = newValue->getOutputModel()->getMode();
        _lastShowTimeStamps = newValue->getOutputModel()->getShowTimeStamps();
        emit logReplaced(getLog());
    }
}
