#include "logvm.hpp"
#include "iomode.hpp"

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
        removedLog = convertToLog(removedPackage);
        removedPackage->deleteLater();
    }

    QString appendedLog = convertToLog(package);
    emit logAdded(appendedLog, removedLog);
}

void LogVM::clear()
{
    receivedPackages.clear();
    emit logReplaced(getLog());
}

void LogVM::uartAvailable(const QByteArray incomeData)
{
    QList<UARTPackage*> appendPackages = pack_data(incomeData);
    if (appendPackages.empty()){
        return;
    }

    UARTPackage* lastPackage = nullptr;
    if (!receivedPackages.empty()){
        lastPackage = receivedPackages.last();
    }

    bool lastPackageValid = false;
    QByteArray firstIncomeData = appendLastPackageData(appendPackages, lastPackage, lastPackageValid);

    QString appendLog;
    if (lastPackage && !lastPackageValid){
        appendLog = convertToLog(firstIncomeData);
    }
    appendLog += fillLog(appendPackages);

    QList<UARTPackage*> removePackages = addPackages(appendPackages);
    QString removeLog = remove(removePackages);

    emit logAdded(appendLog, removeLog);
}

QByteArray LogVM::appendLastPackageData(QList<UARTPackage*> &appendPackages, UARTPackage* lastPackage, bool &lastPackageValid){
    if (lastPackage && !lastPackage->isValid() && !lastPackage->getIsLogOutput()){
        lastPackageValid = false;

        UARTPackage* firstAppendPackage = appendPackages.first();
        QByteArray firstAppendPackageData = firstAppendPackage->getData();

        QByteArray newLastData = lastPackage->getData();
        newLastData.append(firstAppendPackageData);
        lastPackage->setData(newLastData);

        firstAppendPackage = appendPackages.first();
        firstAppendPackage->deleteLater();
        appendPackages.removeFirst();

        return firstAppendPackageData;
    }
    else{
        lastPackageValid = true;
        return "";
    }
}

QString LogVM::fillLog(QList<UARTPackage *> logPackages)
{
    QString appendLog = "";

    foreach (auto package, logPackages){
        auto log = convertToLog(package);
        appendLog += log;
    }

    return appendLog;
}

QList<UARTPackage*> LogVM::pack_data(const QByteArray rx_buffer_data)
{
    QList<UARTPackage*> splitted_packages;

    const QDateTime dateTime = QDateTime::currentDateTime();
    const QString portName = uart->getCurrentPortName();

    QList<QByteArray> splitted_rx;
    int package_begin_index = 0;

    for (int i = 0; i < rx_buffer_data.count(); i++){
        if (rx_buffer_data.at(i) == '\n'){
            QByteArray packageData = rx_buffer_data.mid(package_begin_index, i - package_begin_index + 1);
            splitted_rx.append(packageData);

            package_begin_index = i + 1;
        }
    }

    if (splitted_rx.empty()){
        splitted_rx.append(rx_buffer_data);
    }
    else{
        if (package_begin_index < rx_buffer_data.count()){
            QByteArray packageData = rx_buffer_data.mid(package_begin_index, rx_buffer_data.count() - package_begin_index + 1);
            splitted_rx.append(packageData);
        }
    }

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

QString LogVM::remove(QList<UARTPackage *> packages)
{
    QString removeLog = "";
    if (!packages.isEmpty()){
        removeLog = convertToLog(packages);
        foreach (auto package, packages) {
            package->deleteLater();
        }
    }

    return removeLog;;
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
    QString log = getPackageLabel(package);
    log += convertToLog(package->getData());

    return log;
}

QString LogVM::convertToLog(const QByteArray data){
    switch (getOptionsModel()->getOutputModel()->getMode()) {
    case IOModeEnum::TEXT:
        return convertPackageAsText(data);
    default:
        return convertPackageAsText(data);
    }
}

QString LogVM::convertPackageAsText(const QByteArray data)
{
    QString text = data;
    text.remove('\r');
    return text;
}

QString LogVM::getPackageLabel(const UARTPackage* package)
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
