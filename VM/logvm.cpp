#include "logvm.hpp"

UARTPackage* LogVM::addPackage(UARTPackage *package)
{
    receivedPackages.append(package);
    UARTPackage* firstPackage = nullptr;

    if (receivedPackages.count() > receivedPackages_maxCount){
        firstPackage = receivedPackages.at(0);
        receivedPackages.removeFirst();
    }

    return firstPackage;
}

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
    qDebug() << message;

    UARTPackage* package = new UARTPackage();
    package->setData(message.toUtf8());
    package->setDateTime(QDateTime::currentDateTime());
    package->setIsLogOutput(true);
    UARTPackage* removedPackage = addPackage(package);

    QString removedLog = "";
    if (removedPackage != nullptr){
        removedLog = convertToLog(removedPackage) + "\n";
    }

    QString appendedLog = convertToLog(package) + "\n"; 
    emit logAdded(appendedLog, removedLog);
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
    package->setPortName(uart->getCurrentPortName());
    uart->clearRXBuffer();
    UARTPackage* removedPackage = addPackage(package);

    QString removedLog = "";
    if (removedPackage != nullptr){
        removedLog = convertToLog(removedPackage) + "\n";
    }

    QString appendedLog = convertToLog(package) + "\n";
    emit logAdded(appendedLog, removedLog);
}

QString LogVM::getLog()
{
    QString log;
    for(int i = 0; i < receivedPackages.count(); i++){
        auto package = receivedPackages.at(i);
        log += convertToLog(package) + "\n";
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
        QString hourStr = QString::number(package->getDateTime().time().hour());
        while (hourStr.count() < 2){
            hourStr.prepend("0");
        }
        text.append(hourStr);
        text.append(":");

        QString minStr = QString::number(package->getDateTime().time().minute());
        while (minStr.count() < 2){
            minStr.prepend("0");
        }
        text.append(minStr);
        text.append(":");

        QString secStr = QString::number(package->getDateTime().time().second());
        while (secStr.count() < 2){
            secStr.prepend("0");
        }
        text.append(secStr);
        text.append(":");

        QString msecStr = QString::number(package->getDateTime().time().msec());
        while (msecStr.count() < 3){
            msecStr.append("0");
        }
        text.append(msecStr);
        text.append(" ");
    }

    if (package->getIsLogOutput()){
        text.append("Терминал -> ");
    }
    else{
        text.append(package->getPortName());
        text.append(" -> ");
    }

    text.append(package->getData());
    return text;
}

void LogVM::onOptionsModelChanged()
{
//    OptionsModel* newValue = getOptionsModel();
//    if (_lastDisplayMode != newValue->getOutputModel()->getMode() || _lastShowTimeStamps != newValue->getOutputModel()->getShowTimeStamps()){
//        _lastDisplayMode = newValue->getOutputModel()->getMode();
//        _lastShowTimeStamps = newValue->getOutputModel()->getShowTimeStamps();
        emit logReplaced(getLog());
//    }
}
