#include "optionsvm.hpp"

OptionsVM::OptionsVM(QObject *parent): IOptionsModelDelegateHolder{parent}
{
    connect(this, &OptionsVM::optionsModelChanged, this, &OptionsVM::onOptionsModelChanged);
    connect(this, &OptionsVM::optionsModelChanged, this, [=](){
        qDebug() << "Options model changed:\n" + getOptionsModel()->printable() + "\n";
    });
}

UART *OptionsVM::getUart() const
{
    return uart;
}

void OptionsVM::setUart(UART *newUart)
{
    uart = newUart;
}

OptionsModel* OptionsVM::getOptionsModel()
{
    return optionsModelDelegate->getOptionsModel();
}

void OptionsVM::setOptionsModel(OptionsModel *newOptionsModel)
{
    optionsModelDelegate->setOptionsModel(newOptionsModel);
}

IOptionsModelDelegate *OptionsVM::getOptionsModelDelegate() const
{
    return optionsModelDelegate;
}

void OptionsVM::setOptionsModelDelegate(IOptionsModelDelegate *newDisplayModeDelegate)
{
    optionsModelDelegate = newDisplayModeDelegate;
    connect(optionsModelDelegate, &IOptionsModelDelegate::optionsModelChanged, this, &OptionsVM::optionsModelChanged);
}

void OptionsVM::output(QString message)
{
    getOutputDelegate()->output(message);
}

void OptionsVM::clear()
{
    getOutputDelegate()->clear();
}

IOutputDelegate *OptionsVM::getOutputDelegate() const
{
    return outputDelegate;
}

void OptionsVM::setOutputDelegate(IOutputDelegate *newOutputDelegate)
{
    outputDelegate = newOutputDelegate;
}

QString OptionsVM::getDefaultPortName()
{
    return "отключен";
}

QStringList OptionsVM::getAvailablePortNames()
{
    QStringList defaultValue(getDefaultPortName());
    QStringList available = uart->availablePortNames();
    defaultValue.append(available);
    return defaultValue;
}

void OptionsVM::onOptionsModelChanged()
{

}

void OptionsVM::onFinishedOutputModelEditing()
{
    qDebug("Изменены настройки вывода.\n");
}

void OptionsVM::onFinishedInputModelEditing()
{
    uart->end();

    QString portName = getOptionsModel()->getInputModel()->getPortName();
    bool contains = false;

    auto availablePorts = QSerialPortInfo::availablePorts();
    foreach(auto port, availablePorts){
        if (port.portName() == portName){
            contains = true;
            break;
        }
    }

    if (contains){
        if (!uart->begin(getOptionsModel()->getInputModel())){
            output("Ошибка открытия порта " + getOptionsModel()->getInputModel()->getPortName() + "!\n");
            getOptionsModel()->getInputModel()->setPortName("");
        }
        else{
            output("Новые настройки порта " + getOptionsModel()->getInputModel()->getPortName() + ".\n");
        }
    }
}
