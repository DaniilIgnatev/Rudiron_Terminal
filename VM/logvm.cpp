#include "logvm.hpp"

QList<UARTPackage*> LogVM::split_UART_RX(QByteArray rx_buffer_data)
{
    QList<UARTPackage*> splitted_packages;
    QList<QByteArray> splitted_rx = rx_buffer_data.split('\n');

    const QDateTime dateTime = QDateTime::currentDateTime();
    const QString portName = uart->getCurrentPortName();

    foreach (QByteArray package_data, splitted_rx) {
        UARTPackage* package = new UARTPackage();
        package->setData(package_data);
        package->setDateTime(dateTime);
        package->setPortName(portName);
        splitted_packages.append(package);
    }

    return splitted_packages;
}

QList<UARTPackage*> LogVM::addPackages(QList<UARTPackage *> packages)
{
    QList<UARTPackage*> removedPackages;

    foreach (auto package, packages) {
        UARTPackage* removePackage = addPackage(package);
        if (removePackage){
            removedPackages.append(removePackage);
        }
    }

    return removedPackages;
}

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
        removedPackage->deleteLater();
    }

    QString appendedLog = convertToLog(package) + "\n";
    emit logAdded(appendedLog, removedLog);

    emit logReplaced(getLog());
}

void LogVM::clear()
{
    receivedPackages.clear();
    emit logReplaced(getLog());
}

void LogVM::uartAvailable()
{
    QList<UARTPackage*> packages = split_UART_RX(uart->getRXBuffer());
    uart->clearRXBuffer();
    QList<UARTPackage*> removedPackages = addPackages(packages);

    QString removedLog = "";
    if (!removedPackages.isEmpty()){
        removedLog = convertToLog(removedPackages) + "\n";
        foreach (auto package, removedPackages) {
            package->deleteLater();
        }
    }

    QString appendedLog = convertToLog(packages) + "\n";
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

QString LogVM::convertToLog(QList<UARTPackage *> packages)
{
    QString logPackages = "";

    foreach (auto package, packages) {
        logPackages += convertToLog(package);
    }

    return logPackages;
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
