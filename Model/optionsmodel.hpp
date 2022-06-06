#ifndef OPTIONSMODEL_HPP
#define OPTIONSMODEL_HPP

#include "optionsoutputmodel.hpp"
#include "iobservable.hpp"


class OptionsModel : public IObservable, public IPrintable
{
    Q_OBJECT
    Q_PROPERTY(OptionsOutputModel* outputModel READ getOutputModel WRITE setOutputModel NOTIFY outputModelChanged)
    Q_PROPERTY(QString portName READ getPortName WRITE setPortName NOTIFY portNameChanged)

public:
    explicit OptionsModel(QObject* parent = nullptr);
    explicit OptionsModel(OptionsOutputModel* outputModel, QString portName, QObject* parent = nullptr);

private:
    OptionsOutputModel* _outputModel = nullptr;

    QString _portName;

public:
    Q_INVOKABLE virtual QString printable() override;

    QString getPortName() const;
    void setPortName(const QString &value);

    OptionsOutputModel *getOutputModel() const;
    void setOutputModel(OptionsOutputModel *newOutputModel);

signals:
    void portNameChanged();
    void outputModelChanged();
};


#endif // OPTIONSMODEL_HPP
